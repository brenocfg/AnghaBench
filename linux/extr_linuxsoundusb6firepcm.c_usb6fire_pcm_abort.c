#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sfire_chip {struct pcm_runtime* pcm; } ;
struct TYPE_5__ {scalar_t__ instance; } ;
struct TYPE_8__ {scalar_t__ instance; } ;
struct pcm_runtime {int panic; TYPE_3__* out_urbs; TYPE_2__* in_urbs; TYPE_1__ capture; TYPE_4__ playback; } ;
struct TYPE_7__ {int /*<<< orphan*/  instance; } ;
struct TYPE_6__ {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int PCM_N_URBS ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (scalar_t__) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ *) ; 

void usb6fire_pcm_abort(struct sfire_chip *chip)
{
	struct pcm_runtime *rt = chip->pcm;
	int i;

	if (rt) {
		rt->panic = true;

		if (rt->playback.instance)
			snd_pcm_stop_xrun(rt->playback.instance);

		if (rt->capture.instance)
			snd_pcm_stop_xrun(rt->capture.instance);

		for (i = 0; i < PCM_N_URBS; i++) {
			usb_poison_urb(&rt->in_urbs[i].instance);
			usb_poison_urb(&rt->out_urbs[i].instance);
		}

	}
}