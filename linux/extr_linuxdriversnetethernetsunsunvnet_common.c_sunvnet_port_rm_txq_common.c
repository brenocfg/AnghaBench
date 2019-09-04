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
struct vnet_port {size_t q_index; TYPE_1__* vp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * q_used; int /*<<< orphan*/  nports; } ;

/* Variables and functions */

void sunvnet_port_rm_txq_common(struct vnet_port *port)
{
	port->vp->nports--;
	port->vp->q_used[port->q_index]--;
	port->q_index = 0;
}