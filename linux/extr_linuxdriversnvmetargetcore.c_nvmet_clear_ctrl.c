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
struct nvmet_ctrl {scalar_t__ cc; int /*<<< orphan*/  csts; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_CSTS_RDY ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_clear_ctrl(struct nvmet_ctrl *ctrl)
{
	lockdep_assert_held(&ctrl->lock);

	/* XXX: tear down queues? */
	ctrl->csts &= ~NVME_CSTS_RDY;
	ctrl->cc = 0;
}