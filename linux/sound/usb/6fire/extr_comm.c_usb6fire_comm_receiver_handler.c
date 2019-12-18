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
struct urb {TYPE_2__* dev; scalar_t__ actual_length; scalar_t__ status; struct comm_runtime* context; } ;
struct midi_runtime {int /*<<< orphan*/  (* in_received ) (struct midi_runtime*,int*,int) ;} ;
struct comm_runtime {int* receiver_buffer; TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  shutdown; struct midi_runtime* midi; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct midi_runtime*,int*,int) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb6fire_comm_receiver_handler(struct urb *urb)
{
	struct comm_runtime *rt = urb->context;
	struct midi_runtime *midi_rt = rt->chip->midi;

	if (!urb->status) {
		if (rt->receiver_buffer[0] == 0x10) /* midi in event */
			if (midi_rt)
				midi_rt->in_received(midi_rt,
						rt->receiver_buffer + 2,
						rt->receiver_buffer[1]);
	}

	if (!rt->chip->shutdown) {
		urb->status = 0;
		urb->actual_length = 0;
		if (usb_submit_urb(urb, GFP_ATOMIC) < 0)
			dev_warn(&urb->dev->dev,
					"comm data receiver aborted.\n");
	}
}