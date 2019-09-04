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
 scalar_t__ bm_avg ; 
 scalar_t__ bm_cnt ; 
 int /*<<< orphan*/ * bm_event_thread ; 
 scalar_t__ bm_first ; 
 scalar_t__ bm_last ; 
 scalar_t__ bm_max ; 
 scalar_t__ bm_min ; 
 scalar_t__ bm_std ; 
 scalar_t__ bm_stddev ; 
 int /*<<< orphan*/  bm_str ; 
 scalar_t__ bm_total ; 
 scalar_t__ bm_totalsq ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void trace_benchmark_unreg(void)
{
	if (!bm_event_thread)
		return;

	kthread_stop(bm_event_thread);
	bm_event_thread = NULL;

	strcpy(bm_str, "START");
	bm_total = 0;
	bm_totalsq = 0;
	bm_last = 0;
	bm_max = 0;
	bm_min = 0;
	bm_cnt = 0;
	/* These don't need to be reset but reset them anyway */
	bm_first = 0;
	bm_std = 0;
	bm_avg = 0;
	bm_stddev = 0;
}