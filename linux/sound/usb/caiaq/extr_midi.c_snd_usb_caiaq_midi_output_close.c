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
struct snd_usb_caiaqdev {scalar_t__ midi_out_active; int /*<<< orphan*/  midi_out_urb; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_usb_caiaqdev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_usb_caiaq_midi_output_close(struct snd_rawmidi_substream *substream)
{
	struct snd_usb_caiaqdev *cdev = substream->rmidi->private_data;
	if (cdev->midi_out_active) {
		usb_kill_urb(&cdev->midi_out_urb);
		cdev->midi_out_active = 0;
	}
	return 0;
}