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
struct snd_emu8000 {int fm_chorus_depth; int fm_reverb_depth; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_CCCA_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_CMD (int,int) ; 
 int /*<<< orphan*/  EMU8000_CPF_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_CSL_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_DATA0 (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_DATA1 (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_PSST_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_PTR (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_PTRX_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_VTFT_WRITE (struct snd_emu8000*,int,int) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu8000_poke (struct snd_emu8000*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snd_emu8000_init_fm(struct snd_emu8000 *emu)
{
	unsigned long flags;

	/* Initialize the last two channels for DRAM refresh and producing
	   the reverb and chorus effects for Yamaha OPL-3 synthesizer */

	/* 31: FM left channel, 0xffffe0-0xffffe8 */
	EMU8000_DCYSUSV_WRITE(emu, 30, 0x80);
	EMU8000_PSST_WRITE(emu, 30, 0xFFFFFFE0); /* full left */
	EMU8000_CSL_WRITE(emu, 30, 0x00FFFFE8 | (emu->fm_chorus_depth << 24));
	EMU8000_PTRX_WRITE(emu, 30, (emu->fm_reverb_depth << 8));
	EMU8000_CPF_WRITE(emu, 30, 0);
	EMU8000_CCCA_WRITE(emu, 30, 0x00FFFFE3);

	/* 32: FM right channel, 0xfffff0-0xfffff8 */
	EMU8000_DCYSUSV_WRITE(emu, 31, 0x80);
	EMU8000_PSST_WRITE(emu, 31, 0x00FFFFF0); /* full right */
	EMU8000_CSL_WRITE(emu, 31, 0x00FFFFF8 | (emu->fm_chorus_depth << 24));
	EMU8000_PTRX_WRITE(emu, 31, (emu->fm_reverb_depth << 8));
	EMU8000_CPF_WRITE(emu, 31, 0x8000);
	EMU8000_CCCA_WRITE(emu, 31, 0x00FFFFF3);

	snd_emu8000_poke((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (30)), 0);

	spin_lock_irqsave(&emu->reg_lock, flags);
	while (!(inw(EMU8000_PTR(emu)) & 0x1000))
		;
	while ((inw(EMU8000_PTR(emu)) & 0x1000))
		;
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	snd_emu8000_poke((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (30)), 0x4828);
	/* this is really odd part.. */
	outb(0x3C, EMU8000_PTR(emu));
	outb(0, EMU8000_DATA1(emu));

	/* skew volume & cutoff */
	EMU8000_VTFT_WRITE(emu, 30, 0x8000FFFF);
	EMU8000_VTFT_WRITE(emu, 31, 0x8000FFFF);
}