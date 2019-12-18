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

/* Variables and functions */
 char* examples ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void)
{
	fprintf(stderr, "\nUsage: ./userfaultfd <test type> <MiB> <bounces> "
		"[hugetlbfs_file]\n\n");
	fprintf(stderr, "Supported <test type>: anon, hugetlb, "
		"hugetlb_shared, shmem\n\n");
	fprintf(stderr, "Examples:\n\n");
	fprintf(stderr, "%s", examples);
	exit(1);
}