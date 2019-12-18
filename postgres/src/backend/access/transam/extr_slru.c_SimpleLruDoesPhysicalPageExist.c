#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  SlruCtl ;

/* Variables and functions */
 int BLCKSZ ; 
 scalar_t__ CloseTransientFile (int) ; 
 scalar_t__ ENOENT ; 
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SLRU_CLOSE_FAILED ; 
 int /*<<< orphan*/  SLRU_OPEN_FAILED ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 int /*<<< orphan*/  SLRU_SEEK_FAILED ; 
 int /*<<< orphan*/  SlruFileName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SlruReportIOError (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slru_errcause ; 
 scalar_t__ slru_errno ; 

bool
SimpleLruDoesPhysicalPageExist(SlruCtl ctl, int pageno)
{
	int			segno = pageno / SLRU_PAGES_PER_SEGMENT;
	int			rpageno = pageno % SLRU_PAGES_PER_SEGMENT;
	int			offset = rpageno * BLCKSZ;
	char		path[MAXPGPATH];
	int			fd;
	bool		result;
	off_t		endpos;

	SlruFileName(ctl, path, segno);

	fd = OpenTransientFile(path, O_RDONLY | PG_BINARY);
	if (fd < 0)
	{
		/* expected: file doesn't exist */
		if (errno == ENOENT)
			return false;

		/* report error normally */
		slru_errcause = SLRU_OPEN_FAILED;
		slru_errno = errno;
		SlruReportIOError(ctl, pageno, 0);
	}

	if ((endpos = lseek(fd, 0, SEEK_END)) < 0)
	{
		slru_errcause = SLRU_SEEK_FAILED;
		slru_errno = errno;
		SlruReportIOError(ctl, pageno, 0);
	}

	result = endpos >= (off_t) (offset + BLCKSZ);

	if (CloseTransientFile(fd) != 0)
	{
		slru_errcause = SLRU_CLOSE_FAILED;
		slru_errno = errno;
		return false;
	}

	return result;
}