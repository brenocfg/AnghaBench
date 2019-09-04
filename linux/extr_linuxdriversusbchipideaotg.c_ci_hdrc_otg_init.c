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
struct ci_hdrc {int /*<<< orphan*/  dev; int /*<<< orphan*/  wq; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ci_hdrc_otg_fsm_init (struct ci_hdrc*) ; 
 scalar_t__ ci_otg_is_fsm_mode (struct ci_hdrc*) ; 
 int /*<<< orphan*/  ci_otg_work ; 
 int /*<<< orphan*/  create_freezable_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int ci_hdrc_otg_init(struct ci_hdrc *ci)
{
	INIT_WORK(&ci->work, ci_otg_work);
	ci->wq = create_freezable_workqueue("ci_otg");
	if (!ci->wq) {
		dev_err(ci->dev, "can't create workqueue\n");
		return -ENODEV;
	}

	if (ci_otg_is_fsm_mode(ci))
		return ci_hdrc_otg_fsm_init(ci);

	return 0;
}