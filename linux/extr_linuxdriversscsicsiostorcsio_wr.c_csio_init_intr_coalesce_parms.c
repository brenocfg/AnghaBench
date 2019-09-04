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
struct csio_sge {int dummy; } ;
struct csio_wrm {struct csio_sge sge; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X_TIMERREG_RESTART_COUNTER ; 
 scalar_t__ csio_closest_thresh (struct csio_sge*,scalar_t__) ; 
 int /*<<< orphan*/  csio_closest_timer (struct csio_sge*,int /*<<< orphan*/ ) ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 scalar_t__ csio_intr_coalesce_cnt ; 
 int /*<<< orphan*/  csio_intr_coalesce_time ; 
 scalar_t__ csio_sge_thresh_reg ; 
 int /*<<< orphan*/  csio_sge_timer_reg ; 

__attribute__((used)) static void
csio_init_intr_coalesce_parms(struct csio_hw *hw)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_sge *sge = &wrm->sge;

	csio_sge_thresh_reg = csio_closest_thresh(sge, csio_intr_coalesce_cnt);
	if (csio_intr_coalesce_cnt) {
		csio_sge_thresh_reg = 0;
		csio_sge_timer_reg = X_TIMERREG_RESTART_COUNTER;
		return;
	}

	csio_sge_timer_reg = csio_closest_timer(sge, csio_intr_coalesce_time);
}