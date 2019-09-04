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
struct ast_vhub {scalar_t__ wakeup_en; } ;

/* Variables and functions */
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_ENABLE ; 
 int /*<<< orphan*/  ast_vhub_change_port_stat (struct ast_vhub*,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  ast_vhub_send_host_wakeup (struct ast_vhub*) ; 

void ast_vhub_device_connect(struct ast_vhub *vhub,
			     unsigned int port, bool on)
{
	if (on)
		ast_vhub_change_port_stat(vhub, port, 0,
					  USB_PORT_STAT_CONNECTION, true);
	else
		ast_vhub_change_port_stat(vhub, port,
					  USB_PORT_STAT_CONNECTION |
					  USB_PORT_STAT_ENABLE,
					  0, true);

	/*
	 * If the hub is set to wakup the host on connection events
	 * then send a wakeup.
	 */
	if (vhub->wakeup_en)
		ast_vhub_send_host_wakeup(vhub);
}