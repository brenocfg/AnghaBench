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
struct snd_emu8000 {int last_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ,int) ; 
 int EMU8000_DRAM_VOICES ; 
 int /*<<< orphan*/  EMU8000_HWCF1_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_HWCF2_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_HWCF3_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  init_arrays (struct snd_emu8000*) ; 
 int /*<<< orphan*/  init_audio (struct snd_emu8000*) ; 
 int /*<<< orphan*/  init_dma (struct snd_emu8000*) ; 
 int /*<<< orphan*/  size_dram (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_init_fm (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_update_chorus_mode (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_update_equalizer (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_update_reverb_mode (struct snd_emu8000*) ; 

__attribute__((used)) static void
snd_emu8000_init_hw(struct snd_emu8000 *emu)
{
	int i;

	emu->last_reg = 0xffff; /* reset the last register index */

	/* initialize hardware configuration */
	EMU8000_HWCF1_WRITE(emu, 0x0059);
	EMU8000_HWCF2_WRITE(emu, 0x0020);

	/* disable audio; this seems to reduce a clicking noise a bit.. */
	EMU8000_HWCF3_WRITE(emu, 0);

	/* initialize audio channels */
	init_audio(emu);

	/* initialize DMA */
	init_dma(emu);

	/* initialize init arrays */
	init_arrays(emu);

	/*
	 * Initialize the FM section of the AWE32, this is needed
	 * for DRAM refresh as well
	 */
	snd_emu8000_init_fm(emu);

	/* terminate all voices */
	for (i = 0; i < EMU8000_DRAM_VOICES; i++)
		EMU8000_DCYSUSV_WRITE(emu, 0, 0x807F);
	
	/* check DRAM memory size */
	size_dram(emu);

	/* enable audio */
	EMU8000_HWCF3_WRITE(emu, 0x4);

	/* set equzlier, chorus and reverb modes */
	snd_emu8000_update_equalizer(emu);
	snd_emu8000_update_chorus_mode(emu);
	snd_emu8000_update_reverb_mode(emu);
}