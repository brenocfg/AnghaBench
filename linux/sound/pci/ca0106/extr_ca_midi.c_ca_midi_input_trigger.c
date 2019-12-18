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
struct snd_ca_midi {int /*<<< orphan*/  rx_enable; int /*<<< orphan*/  (* interrupt_disable ) (struct snd_ca_midi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* interrupt_enable ) (struct snd_ca_midi*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev_id; } ;
struct TYPE_2__ {struct snd_ca_midi* private_data; } ;

/* Variables and functions */
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct snd_ca_midi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_ca_midi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca_midi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct snd_ca_midi *midi = substream->rmidi->private_data;

	if (snd_BUG_ON(!midi->dev_id))
		return;

	if (up) {
		midi->interrupt_enable(midi,midi->rx_enable);
	} else {
		midi->interrupt_disable(midi, midi->rx_enable);
	}
}