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
struct TYPE_3__ {int channel; int value; } ;
struct TYPE_4__ {TYPE_1__ control; } ;
struct snd_seq_event {TYPE_2__ data; } ;
struct snd_midi_event {int* buf; } ;

/* Variables and functions */

__attribute__((used)) static void one_param_ctrl_event(struct snd_midi_event *dev, struct snd_seq_event *ev)
{
	ev->data.control.channel = dev->buf[0] & 0x0f;
	ev->data.control.value = dev->buf[1];
}