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
struct urb {struct pcm_urb* context; } ;
struct pcm_urb {TYPE_1__* chip; } ;
struct pcm_runtime {scalar_t__ stream_state; int stream_wait_cond; int /*<<< orphan*/  stream_wait_queue; } ;
struct TYPE_2__ {struct pcm_runtime* pcm; } ;

/* Variables and functions */
 scalar_t__ STREAM_STARTING ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb6fire_pcm_out_urb_handler(struct urb *usb_urb)
{
	struct pcm_urb *urb = usb_urb->context;
	struct pcm_runtime *rt = urb->chip->pcm;

	if (rt->stream_state == STREAM_STARTING) {
		rt->stream_wait_cond = true;
		wake_up(&rt->stream_wait_queue);
	}
}