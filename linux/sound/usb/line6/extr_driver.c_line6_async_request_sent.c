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
struct urb {scalar_t__ context; } ;
struct message {scalar_t__ done; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct message*) ; 
 int /*<<< orphan*/  line6_send_raw_message_async_part (struct message*,struct urb*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void line6_async_request_sent(struct urb *urb)
{
	struct message *msg = (struct message *)urb->context;

	if (msg->done >= msg->size) {
		usb_free_urb(urb);
		kfree(msg);
	} else
		line6_send_raw_message_async_part(msg, urb);
}