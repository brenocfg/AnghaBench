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
struct usb_line6 {int dummy; } ;
struct urb {int dummy; } ;
struct message {char const* buffer; int size; scalar_t__ done; struct usb_line6* line6; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct message*) ; 
 struct message* kmalloc (int,int /*<<< orphan*/ ) ; 
 int line6_send_raw_message_async_part (struct message*,struct urb*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int line6_send_raw_message_async(struct usb_line6 *line6, const char *buffer,
				 int size)
{
	struct message *msg;
	struct urb *urb;

	/* create message: */
	msg = kmalloc(sizeof(struct message), GFP_ATOMIC);
	if (msg == NULL)
		return -ENOMEM;

	/* create URB: */
	urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (urb == NULL) {
		kfree(msg);
		return -ENOMEM;
	}

	/* set message data: */
	msg->line6 = line6;
	msg->buffer = buffer;
	msg->size = size;
	msg->done = 0;

	/* start sending: */
	return line6_send_raw_message_async_part(msg, urb);
}