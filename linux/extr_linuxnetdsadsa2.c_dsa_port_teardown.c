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
struct dsa_port {int type; int /*<<< orphan*/ * slave; int /*<<< orphan*/  devlink_port; } ;

/* Variables and functions */
#define  DSA_PORT_TYPE_CPU 131 
#define  DSA_PORT_TYPE_DSA 130 
#define  DSA_PORT_TYPE_UNUSED 129 
#define  DSA_PORT_TYPE_USER 128 
 int /*<<< orphan*/  devlink_port_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_port_link_unregister_of (struct dsa_port*) ; 
 int /*<<< orphan*/  dsa_slave_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsa_port_teardown(struct dsa_port *dp)
{
	if (dp->type != DSA_PORT_TYPE_UNUSED)
		devlink_port_unregister(&dp->devlink_port);

	switch (dp->type) {
	case DSA_PORT_TYPE_UNUSED:
		break;
	case DSA_PORT_TYPE_CPU:
	case DSA_PORT_TYPE_DSA:
		dsa_port_link_unregister_of(dp);
		break;
	case DSA_PORT_TYPE_USER:
		if (dp->slave) {
			dsa_slave_destroy(dp->slave);
			dp->slave = NULL;
		}
		break;
	}
}