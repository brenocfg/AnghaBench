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
struct device {int dummy; } ;
struct ac97_controller {int /*<<< orphan*/  parent; int /*<<< orphan*/  adap; int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ac97_adapter_idr ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ac97_controller* to_ac97_controller (struct device*) ; 

__attribute__((used)) static void ac97_adapter_release(struct device *dev)
{
	struct ac97_controller *ac97_ctrl;

	ac97_ctrl = to_ac97_controller(dev);
	idr_remove(&ac97_adapter_idr, ac97_ctrl->nr);
	dev_dbg(&ac97_ctrl->adap, "adapter unregistered by %s\n",
		dev_name(ac97_ctrl->parent));
}