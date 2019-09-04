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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_graph_get_remote_port (struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool of_get_remote(struct device_node *epnode,
			  struct device_node **remote_node)
{
	struct device_node *rp, *rpp;
	struct device_node *remote;
	bool is_csi_port;

	rp = of_graph_get_remote_port(epnode);
	rpp = of_graph_get_remote_port_parent(epnode);

	if (of_device_is_compatible(rpp, "fsl,imx6q-ipu")) {
		/* the remote is one of the CSI ports */
		remote = rp;
		of_node_put(rpp);
		is_csi_port = true;
	} else {
		remote = rpp;
		of_node_put(rp);
		is_csi_port = false;
	}

	if (!of_device_is_available(remote)) {
		of_node_put(remote);
		*remote_node = NULL;
	} else {
		*remote_node = remote;
	}

	return is_csi_port;
}