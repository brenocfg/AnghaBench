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
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT1724_IRQ_MPU_RX ; 
 int /*<<< orphan*/  vt1724_enable_midi_irq (struct snd_rawmidi_substream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vt1724_midi_clear_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt1724_midi_input_open(struct snd_rawmidi_substream *s)
{
	vt1724_midi_clear_rx(s->rmidi->private_data);
	vt1724_enable_midi_irq(s, VT1724_IRQ_MPU_RX, 1);
	return 0;
}