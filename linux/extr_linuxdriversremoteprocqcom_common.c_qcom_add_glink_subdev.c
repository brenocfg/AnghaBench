#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* parent; } ;
struct rproc {struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct qcom_rproc_glink {TYPE_2__ subdev; struct device* dev; int /*<<< orphan*/  node; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  glink_subdev_start ; 
 int /*<<< orphan*/  glink_subdev_stop ; 
 int /*<<< orphan*/  of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rproc_add_subdev (struct rproc*,TYPE_2__*) ; 

void qcom_add_glink_subdev(struct rproc *rproc, struct qcom_rproc_glink *glink)
{
	struct device *dev = &rproc->dev;

	glink->node = of_get_child_by_name(dev->parent->of_node, "glink-edge");
	if (!glink->node)
		return;

	glink->dev = dev;
	glink->subdev.start = glink_subdev_start;
	glink->subdev.stop = glink_subdev_stop;

	rproc_add_subdev(rproc, &glink->subdev);
}