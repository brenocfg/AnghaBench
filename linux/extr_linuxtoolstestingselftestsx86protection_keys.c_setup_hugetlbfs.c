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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ GET_NR_HUGE_PAGES ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  __stringify (scalar_t__) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  cat_into_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ geteuid () ; 
 int hugetlb_setup_ok ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

void setup_hugetlbfs(void)
{
	int err;
	int fd;
	char buf[] = "123";

	if (geteuid() != 0) {
		fprintf(stderr, "WARNING: not run as root, can not do hugetlb test\n");
		return;
	}

	cat_into_file(__stringify(GET_NR_HUGE_PAGES), "/proc/sys/vm/nr_hugepages");

	/*
	 * Now go make sure that we got the pages and that they
	 * are 2M pages.  Someone might have made 1G the default.
	 */
	fd = open("/sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages", O_RDONLY);
	if (fd < 0) {
		perror("opening sysfs 2M hugetlb config");
		return;
	}

	/* -1 to guarantee leaving the trailing \0 */
	err = read(fd, buf, sizeof(buf)-1);
	close(fd);
	if (err <= 0) {
		perror("reading sysfs 2M hugetlb config");
		return;
	}

	if (atoi(buf) != GET_NR_HUGE_PAGES) {
		fprintf(stderr, "could not confirm 2M pages, got: '%s' expected %d\n",
			buf, GET_NR_HUGE_PAGES);
		return;
	}

	hugetlb_setup_ok = 1;
}