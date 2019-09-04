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
struct TYPE_2__ {int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  fifo; int /*<<< orphan*/  active; } ;
struct usb_line6 {scalar_t__ message_length; TYPE_1__ messages; int /*<<< orphan*/  buffer_message; } ;

/* Variables and functions */
 scalar_t__ kfifo_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void line6_hwdep_push_message(struct usb_line6 *line6)
{
	if (!line6->messages.active)
		return;

	if (kfifo_avail(&line6->messages.fifo) >= line6->message_length) {
		/* No race condition here, there's only one writer */
		kfifo_in(&line6->messages.fifo,
			line6->buffer_message, line6->message_length);
	} /* else TODO: signal overflow */

	wake_up_interruptible(&line6->messages.wait_queue);
}