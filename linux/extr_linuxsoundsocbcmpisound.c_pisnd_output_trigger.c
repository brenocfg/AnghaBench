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
struct snd_rawmidi_substream {int dummy; } ;

/* Variables and functions */
 struct snd_rawmidi_substream* g_midi_output_substream ; 
 int /*<<< orphan*/  pisnd_spi_start () ; 
 int /*<<< orphan*/  printe (char*) ; 

__attribute__((used)) static void pisnd_output_trigger(
	struct snd_rawmidi_substream *substream,
	int up
	)
{
	if (substream != g_midi_output_substream) {
		printe("MIDI output trigger called for an unexpected stream!");
		return;
	}

	if (!up)
		return;

	pisnd_spi_start();
}