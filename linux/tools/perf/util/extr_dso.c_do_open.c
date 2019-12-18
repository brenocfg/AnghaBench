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
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 scalar_t__ EMFILE ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  close_first_dso () ; 
 int /*<<< orphan*/  dso__data_open_cnt ; 
 scalar_t__ errno ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (scalar_t__,char*,int) ; 

__attribute__((used)) static int do_open(char *name)
{
	int fd;
	char sbuf[STRERR_BUFSIZE];

	do {
		fd = open(name, O_RDONLY|O_CLOEXEC);
		if (fd >= 0)
			return fd;

		pr_debug("dso open failed: %s\n",
			 str_error_r(errno, sbuf, sizeof(sbuf)));
		if (!dso__data_open_cnt || errno != EMFILE)
			break;

		close_first_dso();
	} while (1);

	return -1;
}