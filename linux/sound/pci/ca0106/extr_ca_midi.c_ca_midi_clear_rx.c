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
struct snd_ca_midi {int dummy; } ;

/* Variables and functions */
 scalar_t__ ca_midi_input_avail (struct snd_ca_midi*) ; 
 int /*<<< orphan*/  ca_midi_read_data (struct snd_ca_midi*) ; 
 int /*<<< orphan*/  ca_midi_read_stat (struct snd_ca_midi*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca_midi_clear_rx(struct snd_ca_midi *midi)
{
	int timeout = 100000;
	for (; timeout > 0 && ca_midi_input_avail(midi); timeout--)
		ca_midi_read_data(midi);
#ifdef CONFIG_SND_DEBUG
	if (timeout <= 0)
		pr_err("ca_midi_clear_rx: timeout (status = 0x%x)\n",
			   ca_midi_read_stat(midi));
#endif
}