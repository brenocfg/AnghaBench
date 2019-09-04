#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rocker_world_ops {int (* port_pre_init ) (struct rocker_port*) ;int /*<<< orphan*/  port_priv_size; } ;
struct rocker_port {int /*<<< orphan*/  wpriv; TYPE_1__* rocker; } ;
struct TYPE_2__ {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct rocker_port*) ; 

__attribute__((used)) static int rocker_world_port_pre_init(struct rocker_port *rocker_port)
{
	struct rocker_world_ops *wops = rocker_port->rocker->wops;
	int err;

	rocker_port->wpriv = kzalloc(wops->port_priv_size, GFP_KERNEL);
	if (!rocker_port->wpriv)
		return -ENOMEM;
	if (!wops->port_pre_init)
		return 0;
	err = wops->port_pre_init(rocker_port);
	if (err)
		kfree(rocker_port->wpriv);
	return 0;
}