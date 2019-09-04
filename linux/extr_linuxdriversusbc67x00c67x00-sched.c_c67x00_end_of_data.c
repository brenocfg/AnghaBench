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
struct urb {int transfer_buffer_length; int actual_length; int transfer_flags; int /*<<< orphan*/  pipe; } ;
struct c67x00_td {int /*<<< orphan*/  pipe; struct urb* urb; } ;

/* Variables and functions */
 int URB_ZERO_PACKET ; 
 int td_actual_bytes (struct c67x00_td*) ; 
 int /*<<< orphan*/  td_udev (struct c67x00_td*) ; 
 scalar_t__ unlikely (int) ; 
 int usb_maxpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int c67x00_end_of_data(struct c67x00_td *td)
{
	int maxps, need_empty, remaining;
	struct urb *urb = td->urb;
	int act_bytes;

	act_bytes = td_actual_bytes(td);

	if (unlikely(!act_bytes))
		return 1;	/* This was an empty packet */

	maxps = usb_maxpacket(td_udev(td), td->pipe, usb_pipeout(td->pipe));

	if (unlikely(act_bytes < maxps))
		return 1;	/* Smaller then full packet */

	remaining = urb->transfer_buffer_length - urb->actual_length;
	need_empty = (urb->transfer_flags & URB_ZERO_PACKET) &&
	    usb_pipeout(urb->pipe) && !(remaining % maxps);

	if (unlikely(!remaining && !need_empty))
		return 1;

	return 0;
}