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
typedef  int /*<<< orphan*/  u8 ;
struct urb {void (* complete ) (struct urb*) ;int interval; int /*<<< orphan*/  dev; void* context; int /*<<< orphan*/  pipe; int /*<<< orphan*/ * transfer_buffer; } ;
struct comm_runtime {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_EP ; 
 int /*<<< orphan*/  usb_init_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb6fire_comm_init_urb(struct comm_runtime *rt, struct urb *urb,
		u8 *buffer, void *context, void(*handler)(struct urb *urb))
{
	usb_init_urb(urb);
	urb->transfer_buffer = buffer;
	urb->pipe = usb_sndintpipe(rt->chip->dev, COMM_EP);
	urb->complete = handler;
	urb->context = context;
	urb->interval = 1;
	urb->dev = rt->chip->dev;
}