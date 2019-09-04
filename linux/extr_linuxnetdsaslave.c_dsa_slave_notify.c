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
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  index; TYPE_1__* ds; } ;
struct TYPE_4__ {struct net_device* dev; } ;
struct dsa_notifier_register_info {TYPE_2__ info; struct net_device* master; int /*<<< orphan*/  port_number; int /*<<< orphan*/  switch_number; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_dsa_notifiers (unsigned long,struct net_device*,TYPE_2__*) ; 
 struct net_device* dsa_slave_to_master (struct net_device*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 

__attribute__((used)) static void dsa_slave_notify(struct net_device *dev, unsigned long val)
{
	struct net_device *master = dsa_slave_to_master(dev);
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_notifier_register_info rinfo = {
		.switch_number = dp->ds->index,
		.port_number = dp->index,
		.master = master,
		.info.dev = dev,
	};

	call_dsa_notifiers(val, dev, &rinfo.info);
}