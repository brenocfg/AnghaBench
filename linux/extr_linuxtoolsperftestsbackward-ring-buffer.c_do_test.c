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
struct perf_evlist {int dummy; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int STRERR_BUFSIZE ; 
 int TEST_FAIL ; 
 int count_samples (struct perf_evlist*,int*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  perf_evlist__disable (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__enable (struct perf_evlist*) ; 
 int perf_evlist__mmap (struct perf_evlist*,int) ; 
 int /*<<< orphan*/  perf_evlist__munmap (struct perf_evlist*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  testcase () ; 

__attribute__((used)) static int do_test(struct perf_evlist *evlist, int mmap_pages,
		   int *sample_count, int *comm_count)
{
	int err;
	char sbuf[STRERR_BUFSIZE];

	err = perf_evlist__mmap(evlist, mmap_pages);
	if (err < 0) {
		pr_debug("perf_evlist__mmap: %s\n",
			 str_error_r(errno, sbuf, sizeof(sbuf)));
		return TEST_FAIL;
	}

	perf_evlist__enable(evlist);
	testcase();
	perf_evlist__disable(evlist);

	err = count_samples(evlist, sample_count, comm_count);
	perf_evlist__munmap(evlist);
	return err;
}