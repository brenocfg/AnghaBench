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
 int /*<<< orphan*/  EMU8000_CCCA_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_CSL_WRITE (struct snd_emu8000*,int,int) ; 
 int EMU8000_DRAM_VOICES ; 
 int /*<<< orphan*/  EMU8000_PSST_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_VTFT_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu8000_dma_chan (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  snd_emux_lock_voice (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
snd_emu8000_open_dma(struct snd_emu8000 *emu, int write)
{
	int i;

	/* reserve all 30 voices for loading */
	for (i = 0; i < EMU8000_DRAM_VOICES; i++) {
		snd_emux_lock_voice(emu->emu, i);
		snd_emu8000_dma_chan(emu, i, write);
	}

	/* assign voice 31 and 32 to ROM */
	EMU8000_VTFT_WRITE(emu, 30, 0);
	EMU8000_PSST_WRITE(emu, 30, 0x1d8);
	EMU8000_CSL_WRITE(emu, 30, 0x1e0);
	EMU8000_CCCA_WRITE(emu, 30, 0x1d8);
	EMU8000_VTFT_WRITE(emu, 31, 0);
	EMU8000_PSST_WRITE(emu, 31, 0x1d8);
	EMU8000_CSL_WRITE(emu, 31, 0x1e0);
	EMU8000_CCCA_WRITE(emu, 31, 0x1d8);

	return 0;
}