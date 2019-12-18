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
struct dirty_throttle_control {unsigned long thresh; int /*<<< orphan*/  member_0; } ;
struct bdi_writeback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDTC_INIT (struct bdi_writeback*) ; 
 unsigned long __wb_calc_thresh (struct dirty_throttle_control*) ; 

unsigned long wb_calc_thresh(struct bdi_writeback *wb, unsigned long thresh)
{
	struct dirty_throttle_control gdtc = { GDTC_INIT(wb),
					       .thresh = thresh };
	return __wb_calc_thresh(&gdtc);
}