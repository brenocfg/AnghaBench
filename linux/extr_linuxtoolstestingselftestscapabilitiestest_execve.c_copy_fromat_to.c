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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int openat (int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char*,scalar_t__) ; 

__attribute__((used)) static void copy_fromat_to(int fromfd, const char *fromname, const char *toname)
{
	int from = openat(fromfd, fromname, O_RDONLY);
	if (from == -1)
		ksft_exit_fail_msg("open copy source - %s\n", strerror(errno));

	int to = open(toname, O_CREAT | O_WRONLY | O_EXCL, 0700);

	while (true) {
		char buf[4096];
		ssize_t sz = read(from, buf, sizeof(buf));
		if (sz == 0)
			break;
		if (sz < 0)
			ksft_exit_fail_msg("read - %s\n", strerror(errno));

		if (write(to, buf, sz) != sz)
			/* no short writes on tmpfs */
			ksft_exit_fail_msg("write - %s\n", strerror(errno));
	}

	close(from);
	close(to);
}