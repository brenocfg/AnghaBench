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
struct snd_rawmidi_params {int dummy; } ;

/* Variables and functions */
 int resize_runtime_buffer (int /*<<< orphan*/ ,struct snd_rawmidi_params*,int) ; 
 int /*<<< orphan*/  snd_rawmidi_drain_input (struct snd_rawmidi_substream*) ; 

int snd_rawmidi_input_params(struct snd_rawmidi_substream *substream,
			     struct snd_rawmidi_params *params)
{
	snd_rawmidi_drain_input(substream);
	return resize_runtime_buffer(substream->runtime, params, true);
}