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
struct TYPE_2__ {int /*<<< orphan*/  lp; } ;
struct vnet_port {TYPE_1__ vio; } ;
struct vio_msg_tag {int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int /*<<< orphan*/  ldc_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int vnet_handle_unknown(struct vnet_port *port, void *arg)
{
	struct vio_msg_tag *pkt = arg;

	pr_err("Received unknown msg [%02x:%02x:%04x:%08x]\n",
	       pkt->type, pkt->stype, pkt->stype_env, pkt->sid);
	pr_err("Resetting connection\n");

	ldc_disconnect(port->vio.lp);

	return -ECONNRESET;
}