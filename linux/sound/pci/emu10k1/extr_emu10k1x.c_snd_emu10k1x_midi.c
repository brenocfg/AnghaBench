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
struct emu10k1x_midi {int /*<<< orphan*/  interrupt; int /*<<< orphan*/  ipr_rx; int /*<<< orphan*/  ipr_tx; int /*<<< orphan*/  port; int /*<<< orphan*/  rx_enable; int /*<<< orphan*/  tx_enable; } ;
struct emu10k1x {struct emu10k1x_midi midi; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTE_MIDIRXENABLE ; 
 int /*<<< orphan*/  INTE_MIDITXENABLE ; 
 int /*<<< orphan*/  IPR_MIDIRECVBUFEMPTY ; 
 int /*<<< orphan*/  IPR_MIDITRANSBUFEMPTY ; 
 int /*<<< orphan*/  MUDATA ; 
 int emu10k1x_midi_init (struct emu10k1x*,struct emu10k1x_midi*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_emu10k1x_midi_interrupt ; 

__attribute__((used)) static int snd_emu10k1x_midi(struct emu10k1x *emu)
{
	struct emu10k1x_midi *midi = &emu->midi;
	int err;

	if ((err = emu10k1x_midi_init(emu, midi, 0, "EMU10K1X MPU-401 (UART)")) < 0)
		return err;

	midi->tx_enable = INTE_MIDITXENABLE;
	midi->rx_enable = INTE_MIDIRXENABLE;
	midi->port = MUDATA;
	midi->ipr_tx = IPR_MIDITRANSBUFEMPTY;
	midi->ipr_rx = IPR_MIDIRECVBUFEMPTY;
	midi->interrupt = snd_emu10k1x_midi_interrupt;
	return 0;
}