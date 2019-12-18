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
struct fw_scs1x {int /*<<< orphan*/  input; scalar_t__ input_escape_count; } ;
struct TYPE_2__ {struct fw_scs1x* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct snd_rawmidi_substream*) ; 

__attribute__((used)) static void midi_capture_trigger(struct snd_rawmidi_substream *stream, int up)
{
	struct fw_scs1x *scs = stream->rmidi->private_data;

	if (up) {
		scs->input_escape_count = 0;
		WRITE_ONCE(scs->input, stream);
	} else {
		WRITE_ONCE(scs->input, NULL);
	}
}