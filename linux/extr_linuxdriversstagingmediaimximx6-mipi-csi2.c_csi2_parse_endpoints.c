#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  num_data_lanes; } ;
struct TYPE_4__ {TYPE_2__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_1__ bus; } ;
struct device_node {int dummy; } ;
struct csi2_dev {TYPE_2__ bus; TYPE_3__* dev; int /*<<< orphan*/  sd; } ;
struct TYPE_6__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_MBUS_CSI2 ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (struct device_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int csi2_parse_endpoints(struct csi2_dev *csi2)
{
	struct device_node *node = csi2->dev->of_node;
	struct device_node *epnode;
	struct v4l2_fwnode_endpoint ep;

	epnode = of_graph_get_endpoint_by_regs(node, 0, -1);
	if (!epnode) {
		v4l2_err(&csi2->sd, "failed to get sink endpoint node\n");
		return -EINVAL;
	}

	v4l2_fwnode_endpoint_parse(of_fwnode_handle(epnode), &ep);
	of_node_put(epnode);

	if (ep.bus_type != V4L2_MBUS_CSI2) {
		v4l2_err(&csi2->sd, "invalid bus type, must be MIPI CSI2\n");
		return -EINVAL;
	}

	csi2->bus = ep.bus.mipi_csi2;

	dev_dbg(csi2->dev, "data lanes: %d\n", csi2->bus.num_data_lanes);
	dev_dbg(csi2->dev, "flags: 0x%08x\n", csi2->bus.flags);
	return 0;
}