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
struct rproc {int dummy; } ;
struct qcom_rproc_glink {int /*<<< orphan*/  node; int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_remove_subdev (struct rproc*,int /*<<< orphan*/ *) ; 

void qcom_remove_glink_subdev(struct rproc *rproc, struct qcom_rproc_glink *glink)
{
	if (!glink->node)
		return;

	rproc_remove_subdev(rproc, &glink->subdev);
	of_node_put(glink->node);
}