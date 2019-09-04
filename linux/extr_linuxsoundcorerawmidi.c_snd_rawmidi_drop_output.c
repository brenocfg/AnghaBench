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
struct snd_rawmidi_substream {int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_runtime_ptrs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_rawmidi_output_trigger (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 

int snd_rawmidi_drop_output(struct snd_rawmidi_substream *substream)
{
	snd_rawmidi_output_trigger(substream, 0);
	reset_runtime_ptrs(substream->runtime, false);
	return 0;
}