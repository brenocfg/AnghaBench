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
struct pcm_runtime {scalar_t__ stream_state; TYPE_2__* out_urbs; TYPE_1__* in_urbs; TYPE_3__* chip; } ;
struct control_runtime {int usb_streaming; int /*<<< orphan*/  (* update_streaming ) (struct control_runtime*) ;} ;
struct TYPE_6__ {struct control_runtime* control; } ;
struct TYPE_5__ {int /*<<< orphan*/  instance; } ;
struct TYPE_4__ {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int PCM_N_URBS ; 
 scalar_t__ STREAM_DISABLED ; 
 scalar_t__ STREAM_STOPPING ; 
 int /*<<< orphan*/  stub1 (struct control_runtime*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb6fire_pcm_stream_stop(struct pcm_runtime *rt)
{
	int i;
	struct control_runtime *ctrl_rt = rt->chip->control;

	if (rt->stream_state != STREAM_DISABLED) {

		rt->stream_state = STREAM_STOPPING;

		for (i = 0; i < PCM_N_URBS; i++) {
			usb_kill_urb(&rt->in_urbs[i].instance);
			usb_kill_urb(&rt->out_urbs[i].instance);
		}
		ctrl_rt->usb_streaming = false;
		ctrl_rt->update_streaming(ctrl_rt);
		rt->stream_state = STREAM_DISABLED;
	}
}