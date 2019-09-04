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
typedef  size_t u8 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct ast_vhub_port {TYPE_2__ dev; } ;
struct ast_vhub {int speed; struct ast_vhub_port* ports; } ;
struct TYPE_3__ {int max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCDBG (struct ast_vhub*,char*,int) ; 
 int USB_PORT_STAT_ENABLE ; 
 int USB_PORT_STAT_HIGH_SPEED ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int USB_PORT_STAT_RESET ; 
 int USB_PORT_STAT_SUSPEND ; 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ast_vhub_change_port_stat (struct ast_vhub*,size_t,int,int,int) ; 
 int /*<<< orphan*/  ast_vhub_dev_reset (TYPE_2__*) ; 

__attribute__((used)) static void ast_vhub_port_reset(struct ast_vhub *vhub, u8 port)
{
	struct ast_vhub_port *p = &vhub->ports[port];
	u16 set, clr, speed;

	/* First mark disabled */
	ast_vhub_change_port_stat(vhub, port,
				  USB_PORT_STAT_ENABLE |
				  USB_PORT_STAT_SUSPEND,
				  USB_PORT_STAT_RESET,
				  false);

	if (!p->dev.driver)
		return;

	/*
	 * This will either "start" the port or reset the
	 * device if already started...
	 */
	ast_vhub_dev_reset(&p->dev);

	/* Grab the right speed */
	speed = p->dev.driver->max_speed;
	if (speed == USB_SPEED_UNKNOWN || speed > vhub->speed)
		speed = vhub->speed;

	switch (speed) {
	case USB_SPEED_LOW:
		set = USB_PORT_STAT_LOW_SPEED;
		clr = USB_PORT_STAT_HIGH_SPEED;
		break;
	case USB_SPEED_FULL:
		set = 0;
		clr = USB_PORT_STAT_LOW_SPEED |
			USB_PORT_STAT_HIGH_SPEED;
		break;
	case USB_SPEED_HIGH:
		set = USB_PORT_STAT_HIGH_SPEED;
		clr = USB_PORT_STAT_LOW_SPEED;
		break;
	default:
		UDCDBG(vhub, "Unsupported speed %d when"
		       " connecting device\n",
		       speed);
		return;
	}
	clr |= USB_PORT_STAT_RESET;
	set |= USB_PORT_STAT_ENABLE;

	/* This should ideally be delayed ... */
	ast_vhub_change_port_stat(vhub, port, clr, set, true);
}