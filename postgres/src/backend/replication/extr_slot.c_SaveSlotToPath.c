#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cp ;
struct TYPE_7__ {int dirty; int just_dirtied; int /*<<< orphan*/  io_in_progress_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  checksum; int /*<<< orphan*/  slotdata; int /*<<< orphan*/  length; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  ReplicationSlotPersistentData ;
typedef  TYPE_1__ ReplicationSlotOnDisk ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CRC32C (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CloseTransientFile (int) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FIN_CRC32C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_CRC32C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXPGPATH ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  ReplicationSlotOnDiskV2Size ; 
 int /*<<< orphan*/  SLOT_MAGIC ; 
 int /*<<< orphan*/  SLOT_VERSION ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SnapBuildOnDiskChecksummedSize ; 
 int SnapBuildOnDiskNotChecksummedSize ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_EVENT_REPLICATION_SLOT_SYNC ; 
 int /*<<< orphan*/  WAIT_EVENT_REPLICATION_SLOT_WRITE ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  fsync_fname (char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pg_fsync (int) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int write (int,TYPE_1__*,int) ; 

__attribute__((used)) static void
SaveSlotToPath(ReplicationSlot *slot, const char *dir, int elevel)
{
	char		tmppath[MAXPGPATH];
	char		path[MAXPGPATH];
	int			fd;
	ReplicationSlotOnDisk cp;
	bool		was_dirty;

	/* first check whether there's something to write out */
	SpinLockAcquire(&slot->mutex);
	was_dirty = slot->dirty;
	slot->just_dirtied = false;
	SpinLockRelease(&slot->mutex);

	/* and don't do anything if there's nothing to write */
	if (!was_dirty)
		return;

	LWLockAcquire(&slot->io_in_progress_lock, LW_EXCLUSIVE);

	/* silence valgrind :( */
	memset(&cp, 0, sizeof(ReplicationSlotOnDisk));

	sprintf(tmppath, "%s/state.tmp", dir);
	sprintf(path, "%s/state", dir);

	fd = OpenTransientFile(tmppath, O_CREAT | O_EXCL | O_WRONLY | PG_BINARY);
	if (fd < 0)
	{
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not create file \"%s\": %m",
						tmppath)));
		return;
	}

	cp.magic = SLOT_MAGIC;
	INIT_CRC32C(cp.checksum);
	cp.version = SLOT_VERSION;
	cp.length = ReplicationSlotOnDiskV2Size;

	SpinLockAcquire(&slot->mutex);

	memcpy(&cp.slotdata, &slot->data, sizeof(ReplicationSlotPersistentData));

	SpinLockRelease(&slot->mutex);

	COMP_CRC32C(cp.checksum,
				(char *) (&cp) + SnapBuildOnDiskNotChecksummedSize,
				SnapBuildOnDiskChecksummedSize);
	FIN_CRC32C(cp.checksum);

	errno = 0;
	pgstat_report_wait_start(WAIT_EVENT_REPLICATION_SLOT_WRITE);
	if ((write(fd, &cp, sizeof(cp))) != sizeof(cp))
	{
		int			save_errno = errno;

		pgstat_report_wait_end();
		CloseTransientFile(fd);

		/* if write didn't set errno, assume problem is no disk space */
		errno = save_errno ? save_errno : ENOSPC;
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not write to file \"%s\": %m",
						tmppath)));
		return;
	}
	pgstat_report_wait_end();

	/* fsync the temporary file */
	pgstat_report_wait_start(WAIT_EVENT_REPLICATION_SLOT_SYNC);
	if (pg_fsync(fd) != 0)
	{
		int			save_errno = errno;

		pgstat_report_wait_end();
		CloseTransientFile(fd);
		errno = save_errno;
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not fsync file \"%s\": %m",
						tmppath)));
		return;
	}
	pgstat_report_wait_end();

	if (CloseTransientFile(fd) != 0)
	{
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not close file \"%s\": %m",
						tmppath)));
		return;
	}

	/* rename to permanent file, fsync file and directory */
	if (rename(tmppath, path) != 0)
	{
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not rename file \"%s\" to \"%s\": %m",
						tmppath, path)));
		return;
	}

	/*
	 * Check CreateSlotOnDisk() for the reasoning of using a critical section.
	 */
	START_CRIT_SECTION();

	fsync_fname(path, false);
	fsync_fname(dir, true);
	fsync_fname("pg_replslot", true);

	END_CRIT_SECTION();

	/*
	 * Successfully wrote, unset dirty bit, unless somebody dirtied again
	 * already.
	 */
	SpinLockAcquire(&slot->mutex);
	if (!slot->just_dirtied)
		slot->dirty = false;
	SpinLockRelease(&slot->mutex);

	LWLockRelease(&slot->io_in_progress_lock);
}