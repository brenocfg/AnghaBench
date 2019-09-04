#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_composite_dev {TYPE_2__* gadget; } ;
struct TYPE_6__ {TYPE_1__* config; } ;
struct gserial {TYPE_3__ func; } ;
struct f_obex {int /*<<< orphan*/  port_num; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct f_obex* port_to_obex (struct gserial*) ; 
 int usb_function_activate (TYPE_3__*) ; 

__attribute__((used)) static void obex_connect(struct gserial *g)
{
	struct f_obex		*obex = port_to_obex(g);
	struct usb_composite_dev *cdev = g->func.config->cdev;
	int			status;

	status = usb_function_activate(&g->func);
	if (status)
		dev_dbg(&cdev->gadget->dev,
			"obex ttyGS%d function activate --> %d\n",
			obex->port_num, status);
}