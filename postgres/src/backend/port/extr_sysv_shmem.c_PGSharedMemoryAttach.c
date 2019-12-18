#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct shmid_ds {scalar_t__ shm_nattch; } ;
struct TYPE_3__ {scalar_t__ magic; scalar_t__ device; scalar_t__ inode; } ;
typedef  TYPE_1__ PGShmemHeader ;
typedef  int /*<<< orphan*/  IpcMemoryState ;
typedef  int /*<<< orphan*/  IpcMemoryId ;

/* Variables and functions */
 int /*<<< orphan*/  DataDir ; 
 scalar_t__ EACCES ; 
 scalar_t__ EIDRM ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IPC_STAT ; 
 scalar_t__ PGShmemMagic ; 
 int /*<<< orphan*/  PG_SHMAT_FLAGS ; 
 int /*<<< orphan*/  SHMSTATE_ANALYSIS_FAILURE ; 
 int /*<<< orphan*/  SHMSTATE_ATTACHED ; 
 int /*<<< orphan*/  SHMSTATE_ENOENT ; 
 int /*<<< orphan*/  SHMSTATE_FOREIGN ; 
 int /*<<< orphan*/  SHMSTATE_UNATTACHED ; 
 scalar_t__ errno ; 
 scalar_t__ shmat (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct shmid_ds*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static IpcMemoryState
PGSharedMemoryAttach(IpcMemoryId shmId,
					 void *attachAt,
					 PGShmemHeader **addr)
{
	struct shmid_ds shmStat;
	struct stat statbuf;
	PGShmemHeader *hdr;

	*addr = NULL;

	/*
	 * First, try to stat the shm segment ID, to see if it exists at all.
	 */
	if (shmctl(shmId, IPC_STAT, &shmStat) < 0)
	{
		/*
		 * EINVAL actually has multiple possible causes documented in the
		 * shmctl man page, but we assume it must mean the segment no longer
		 * exists.
		 */
		if (errno == EINVAL)
			return SHMSTATE_ENOENT;

		/*
		 * EACCES implies we have no read permission, which means it is not a
		 * Postgres shmem segment (or at least, not one that is relevant to
		 * our data directory).
		 */
		if (errno == EACCES)
			return SHMSTATE_FOREIGN;

		/*
		 * Some Linux kernel versions (in fact, all of them as of July 2007)
		 * sometimes return EIDRM when EINVAL is correct.  The Linux kernel
		 * actually does not have any internal state that would justify
		 * returning EIDRM, so we can get away with assuming that EIDRM is
		 * equivalent to EINVAL on that platform.
		 */
#ifdef HAVE_LINUX_EIDRM_BUG
		if (errno == EIDRM)
			return SHMSTATE_ENOENT;
#endif

		/*
		 * Otherwise, we had better assume that the segment is in use.  The
		 * only likely case is (non-Linux, assumed spec-compliant) EIDRM,
		 * which implies that the segment has been IPC_RMID'd but there are
		 * still processes attached to it.
		 */
		return SHMSTATE_ANALYSIS_FAILURE;
	}

	/*
	 * Try to attach to the segment and see if it matches our data directory.
	 * This avoids any risk of duplicate-shmem-key conflicts on machines that
	 * are running several postmasters under the same userid.
	 *
	 * (When we're called from PGSharedMemoryCreate, this stat call is
	 * duplicative; but since this isn't a high-traffic case it's not worth
	 * trying to optimize.)
	 */
	if (stat(DataDir, &statbuf) < 0)
		return SHMSTATE_ANALYSIS_FAILURE;	/* can't stat; be conservative */

	hdr = (PGShmemHeader *) shmat(shmId, attachAt, PG_SHMAT_FLAGS);
	if (hdr == (PGShmemHeader *) -1)
	{
		/*
		 * Attachment failed.  The cases we're interested in are the same as
		 * for the shmctl() call above.  In particular, note that the owning
		 * postmaster could have terminated and removed the segment between
		 * shmctl() and shmat().
		 *
		 * If attachAt isn't NULL, it's possible that EINVAL reflects a
		 * problem with that address not a vanished segment, so it's best to
		 * pass NULL when probing for conflicting segments.
		 */
		if (errno == EINVAL)
			return SHMSTATE_ENOENT; /* segment disappeared */
		if (errno == EACCES)
			return SHMSTATE_FOREIGN;	/* must be non-Postgres */
#ifdef HAVE_LINUX_EIDRM_BUG
		if (errno == EIDRM)
			return SHMSTATE_ENOENT; /* segment disappeared */
#endif
		/* Otherwise, be conservative. */
		return SHMSTATE_ANALYSIS_FAILURE;
	}
	*addr = hdr;

	if (hdr->magic != PGShmemMagic ||
		hdr->device != statbuf.st_dev ||
		hdr->inode != statbuf.st_ino)
	{
		/*
		 * It's either not a Postgres segment, or not one for my data
		 * directory.
		 */
		return SHMSTATE_FOREIGN;
	}

	/*
	 * It does match our data directory, so now test whether any processes are
	 * still attached to it.  (We are, now, but the shm_nattch result is from
	 * before we attached to it.)
	 */
	return shmStat.shm_nattch == 0 ? SHMSTATE_UNATTACHED : SHMSTATE_ATTACHED;
}