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
 int /*<<< orphan*/  TASK_PROCESS ; 
 int /*<<< orphan*/ * pisnd_midi_recv_callback ; 
 int /*<<< orphan*/  pisnd_schedule_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pisnd_spi_set_callback (int /*<<< orphan*/ *,struct snd_rawmidi_substream*) ; 

__attribute__((used)) static void pisnd_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	if (up) {
		pisnd_spi_set_callback(pisnd_midi_recv_callback, substream);
		pisnd_schedule_process(TASK_PROCESS);
	} else {
		pisnd_spi_set_callback(NULL, NULL);
	}
}