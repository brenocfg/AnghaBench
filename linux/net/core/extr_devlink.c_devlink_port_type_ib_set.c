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
struct ib_device {int dummy; } ;
struct devlink_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_TYPE_IB ; 
 int /*<<< orphan*/  __devlink_port_type_set (struct devlink_port*,int /*<<< orphan*/ ,struct ib_device*) ; 

void devlink_port_type_ib_set(struct devlink_port *devlink_port,
			      struct ib_device *ibdev)
{
	__devlink_port_type_set(devlink_port, DEVLINK_PORT_TYPE_IB, ibdev);
}