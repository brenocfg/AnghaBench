#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {TYPE_1__* shared; } ;
struct TYPE_5__ {int /*<<< orphan*/ * page_buffer; } ;
typedef  TYPE_1__* SlruShared ;
typedef  TYPE_2__* SlruCtl ;

/* Variables and functions */
 int BLCKSZ ; 
 scalar_t__ CloseTransientFile (int) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  InRecovery ; 
 int /*<<< orphan*/  LOG ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int O_RDONLY ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SLRU_CLOSE_FAILED ; 
 int /*<<< orphan*/  SLRU_OPEN_FAILED ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 int /*<<< orphan*/  SLRU_READ_FAILED ; 
 int /*<<< orphan*/  SLRU_SEEK_FAILED ; 
 int /*<<< orphan*/  SlruFileName (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  WAIT_EVENT_SLRU_READ ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slru_errcause ; 
 scalar_t__ slru_errno ; 

__attribute__((used)) static bool
SlruPhysicalReadPage(SlruCtl ctl, int pageno, int slotno)
{
	SlruShared	shared = ctl->shared;
	int			segno = pageno / SLRU_PAGES_PER_SEGMENT;
	int			rpageno = pageno % SLRU_PAGES_PER_SEGMENT;
	int			offset = rpageno * BLCKSZ;
	char		path[MAXPGPATH];
	int			fd;

	SlruFileName(ctl, path, segno);

	/*
	 * In a crash-and-restart situation, it's possible for us to receive
	 * commands to set the commit status of transactions whose bits are in
	 * already-truncated segments of the commit log (see notes in
	 * SlruPhysicalWritePage).  Hence, if we are InRecovery, allow the case
	 * where the file doesn't exist, and return zeroes instead.
	 */
	fd = OpenTransientFile(path, O_RDONLY | PG_BINARY);
	if (fd < 0)
	{
		if (errno != ENOENT || !InRecovery)
		{
			slru_errcause = SLRU_OPEN_FAILED;
			slru_errno = errno;
			return false;
		}

		ereport(LOG,
				(errmsg("file \"%s\" doesn't exist, reading as zeroes",
						path)));
		MemSet(shared->page_buffer[slotno], 0, BLCKSZ);
		return true;
	}

	if (lseek(fd, (off_t) offset, SEEK_SET) < 0)
	{
		slru_errcause = SLRU_SEEK_FAILED;
		slru_errno = errno;
		CloseTransientFile(fd);
		return false;
	}

	errno = 0;
	pgstat_report_wait_start(WAIT_EVENT_SLRU_READ);
	if (read(fd, shared->page_buffer[slotno], BLCKSZ) != BLCKSZ)
	{
		pgstat_report_wait_end();
		slru_errcause = SLRU_READ_FAILED;
		slru_errno = errno;
		CloseTransientFile(fd);
		return false;
	}
	pgstat_report_wait_end();

	if (CloseTransientFile(fd) != 0)
	{
		slru_errcause = SLRU_CLOSE_FAILED;
		slru_errno = errno;
		return false;
	}

	return true;
}