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
struct snd_emu8000 {int /*<<< orphan*/  emu; } ;

/* Variables and functions */
 int EMU8000_DRAM_VOICES ; 
 int /*<<< orphan*/  EMU8000_RAM_CLOSE ; 
 int /*<<< orphan*/  snd_emu8000_dma_chan (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emux_unlock_voice (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
emu8k_close_dram(struct snd_emu8000 *emu)
{
	int i;

	for (i = 0; i < 2; i++)
		snd_emux_unlock_voice(emu->emu, i);
	for (; i < EMU8000_DRAM_VOICES; i++) {
		snd_emu8000_dma_chan(emu, i, EMU8000_RAM_CLOSE);
		snd_emux_unlock_voice(emu->emu, i);
	}
}