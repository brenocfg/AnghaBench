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
struct nvmet_ctrl {int kato; int /*<<< orphan*/  ka_work; int /*<<< orphan*/  csts; int /*<<< orphan*/  cc; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NVME_CSTS_CFS ; 
 int /*<<< orphan*/  NVME_CSTS_RDY ; 
 scalar_t__ NVME_NVM_IOCQES ; 
 scalar_t__ NVME_NVM_IOSQES ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nvmet_cc_ams (int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_cc_css (int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_cc_iocqes (int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_cc_iosqes (int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_cc_mps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void nvmet_start_ctrl(struct nvmet_ctrl *ctrl)
{
	lockdep_assert_held(&ctrl->lock);

	if (nvmet_cc_iosqes(ctrl->cc) != NVME_NVM_IOSQES ||
	    nvmet_cc_iocqes(ctrl->cc) != NVME_NVM_IOCQES ||
	    nvmet_cc_mps(ctrl->cc) != 0 ||
	    nvmet_cc_ams(ctrl->cc) != 0 ||
	    nvmet_cc_css(ctrl->cc) != 0) {
		ctrl->csts = NVME_CSTS_CFS;
		return;
	}

	ctrl->csts = NVME_CSTS_RDY;

	/*
	 * Controllers that are not yet enabled should not really enforce the
	 * keep alive timeout, but we still want to track a timeout and cleanup
	 * in case a host died before it enabled the controller.  Hence, simply
	 * reset the keep alive timer when the controller is enabled.
	 */
	mod_delayed_work(system_wq, &ctrl->ka_work, ctrl->kato * HZ);
}