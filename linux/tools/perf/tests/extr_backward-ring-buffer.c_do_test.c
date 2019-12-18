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
struct evlist {int dummy; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int STRERR_BUFSIZE ; 
 int TEST_FAIL ; 
 int count_samples (struct evlist*,int*,int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  evlist__disable (struct evlist*) ; 
 int /*<<< orphan*/  evlist__enable (struct evlist*) ; 
 int evlist__mmap (struct evlist*,int) ; 
 int /*<<< orphan*/  evlist__munmap (struct evlist*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  testcase () ; 

__attribute__((used)) static int do_test(struct evlist *evlist, int mmap_pages,
		   int *sample_count, int *comm_count)
{
	int err;
	char sbuf[STRERR_BUFSIZE];

	err = evlist__mmap(evlist, mmap_pages);
	if (err < 0) {
		pr_debug("evlist__mmap: %s\n",
			 str_error_r(errno, sbuf, sizeof(sbuf)));
		return TEST_FAIL;
	}

	evlist__enable(evlist);
	testcase();
	evlist__disable(evlist);

	err = count_samples(evlist, sample_count, comm_count);
	evlist__munmap(evlist);
	return err;
}