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
struct snd_rawmidi {struct snd_line6_midi* private_data; } ;
struct snd_line6_midi {int /*<<< orphan*/  midibuf_out; int /*<<< orphan*/  midibuf_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_line6_midi*) ; 
 int /*<<< orphan*/  line6_midibuf_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_line6_midi_free(struct snd_rawmidi *rmidi)
{
	struct snd_line6_midi *line6midi = rmidi->private_data;

	line6_midibuf_destroy(&line6midi->midibuf_in);
	line6_midibuf_destroy(&line6midi->midibuf_out);
	kfree(line6midi);
}