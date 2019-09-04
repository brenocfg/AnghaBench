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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct fw_scs1x {int /*<<< orphan*/  output_idle; int /*<<< orphan*/  idle_wait; } ;
struct TYPE_2__ {struct fw_scs1x* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void midi_playback_drain(struct snd_rawmidi_substream *stream)
{
	struct fw_scs1x *scs = stream->rmidi->private_data;

	wait_event(scs->idle_wait, scs->output_idle);
}