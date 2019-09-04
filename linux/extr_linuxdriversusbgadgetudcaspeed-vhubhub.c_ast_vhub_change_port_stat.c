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
typedef  int u16 ;
struct ast_vhub_port {int status; int change; int /*<<< orphan*/  dev; } ;
struct ast_vhub {struct ast_vhub_port* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDBG (int /*<<< orphan*/ *,char*,unsigned int,int,int,int) ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_C_ENABLE ; 
 int USB_PORT_STAT_C_L1 ; 
 int USB_PORT_STAT_C_OVERCURRENT ; 
 int USB_PORT_STAT_C_RESET ; 
 int USB_PORT_STAT_C_SUSPEND ; 
 int /*<<< orphan*/  ast_vhub_update_hub_ep1 (struct ast_vhub*,unsigned int) ; 

__attribute__((used)) static void ast_vhub_change_port_stat(struct ast_vhub *vhub,
				      unsigned int port,
				      u16 clr_flags,
				      u16 set_flags,
				      bool set_c)
{
	struct ast_vhub_port *p = &vhub->ports[port];
	u16 prev;

	/* Update port status */
	prev = p->status;
	p->status = (prev & ~clr_flags) | set_flags;
	DDBG(&p->dev, "port %d status %04x -> %04x (C=%d)\n",
	     port + 1, prev, p->status, set_c);

	/* Update change bits if needed */
	if (set_c) {
		u16 chg = p->status ^ prev;

		/* Only these are relevant for change */
		chg &= USB_PORT_STAT_C_CONNECTION |
		       USB_PORT_STAT_C_ENABLE |
		       USB_PORT_STAT_C_SUSPEND |
		       USB_PORT_STAT_C_OVERCURRENT |
		       USB_PORT_STAT_C_RESET |
		       USB_PORT_STAT_C_L1;
		p->change |= chg;

		ast_vhub_update_hub_ep1(vhub, port);
	}
}