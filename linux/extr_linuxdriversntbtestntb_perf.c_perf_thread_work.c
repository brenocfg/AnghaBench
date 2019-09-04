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
struct work_struct {int dummy; } ;
struct perf_thread {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_clear_test (struct perf_thread*) ; 
 int perf_init_test (struct perf_thread*) ; 
 int perf_run_test (struct perf_thread*) ; 
 int perf_sync_test (struct perf_thread*) ; 
 struct perf_thread* to_thread_work (struct work_struct*) ; 

__attribute__((used)) static void perf_thread_work(struct work_struct *work)
{
	struct perf_thread *pthr = to_thread_work(work);
	int ret;

	/*
	 * Perform stages in compliance with use_dma flag value.
	 * Test status is changed only if error happened, otherwise
	 * status -ENODATA is kept while test is on-fly. Results
	 * synchronization is performed only if test fininshed
	 * without an error or interruption.
	 */
	ret = perf_init_test(pthr);
	if (ret) {
		pthr->status = ret;
		return;
	}

	ret = perf_run_test(pthr);
	if (ret) {
		pthr->status = ret;
		goto err_clear_test;
	}

	pthr->status = perf_sync_test(pthr);

err_clear_test:
	perf_clear_test(pthr);
}