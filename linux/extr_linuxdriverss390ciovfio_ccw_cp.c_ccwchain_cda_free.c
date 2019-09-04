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
typedef  scalar_t__ u64 ;
struct ccwchain {struct ccw1* ch_ccw; } ;
struct ccw1 {scalar_t__ cda; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ ccw_is_noop (struct ccw1*) ; 
 scalar_t__ ccw_is_test (struct ccw1*) ; 
 scalar_t__ ccw_is_tic (struct ccw1*) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void ccwchain_cda_free(struct ccwchain *chain, int idx)
{
	struct ccw1 *ccw = chain->ch_ccw + idx;

	if (ccw_is_test(ccw) || ccw_is_noop(ccw) || ccw_is_tic(ccw))
		return;
	if (!ccw->count)
		return;

	kfree((void *)(u64)ccw->cda);
}