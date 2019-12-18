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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ dry_run ; 
 int /*<<< orphan*/  dstfd ; 
 int /*<<< orphan*/  dstpath ; 
 scalar_t__ errno ; 
 size_t fetch_done ; 
 int lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progress_report (int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void
write_target_range(char *buf, off_t begin, size_t size)
{
	int			writeleft;
	char	   *p;

	/* update progress report */
	fetch_done += size;
	progress_report(false);

	if (dry_run)
		return;

	if (lseek(dstfd, begin, SEEK_SET) == -1)
		pg_fatal("could not seek in target file \"%s\": %m",
				 dstpath);

	writeleft = size;
	p = buf;
	while (writeleft > 0)
	{
		int			writelen;

		errno = 0;
		writelen = write(dstfd, p, writeleft);
		if (writelen < 0)
		{
			/* if write didn't set errno, assume problem is no disk space */
			if (errno == 0)
				errno = ENOSPC;
			pg_fatal("could not write file \"%s\": %m",
					 dstpath);
		}

		p += writelen;
		writeleft -= writelen;
	}

	/* keep the file open, in case we need to copy more blocks in it */
}