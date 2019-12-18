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
struct snd_emu8k_pcm {unsigned int* panning; unsigned int buf_size; scalar_t__* loop_start; int /*<<< orphan*/  pitch; struct snd_emu8000* emu; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_0080_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_00A0_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_ATKHLDV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_ATKHLD_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_CCCA_WRITE (struct snd_emu8000*,int,unsigned int) ; 
 int /*<<< orphan*/  EMU8000_CPF_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_CSL_WRITE (struct snd_emu8000*,int,unsigned int) ; 
 int /*<<< orphan*/  EMU8000_CVCF_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_DCYSUS_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_ENVVAL_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_ENVVOL_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_FM2FRQ2_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_FMMOD_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_IP_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_LFO1VAL_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_LFO2VAL_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_PEFE_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_PSST_WRITE (struct snd_emu8000*,int,unsigned int) ; 
 int /*<<< orphan*/  EMU8000_PTRX_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_TREMFRQ_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_VTFT_WRITE (struct snd_emu8000*,int,int) ; 

__attribute__((used)) static void setup_voice(struct snd_emu8k_pcm *rec, int ch)
{
	struct snd_emu8000 *hw = rec->emu;
	unsigned int temp;

	/* channel to be silent and idle */
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x0080);
	EMU8000_VTFT_WRITE(hw, ch, 0x0000FFFF);
	EMU8000_CVCF_WRITE(hw, ch, 0x0000FFFF);
	EMU8000_PTRX_WRITE(hw, ch, 0);
	EMU8000_CPF_WRITE(hw, ch, 0);

	/* pitch offset */
	EMU8000_IP_WRITE(hw, ch, rec->pitch);
	/* set envelope parameters */
	EMU8000_ENVVAL_WRITE(hw, ch, 0x8000);
	EMU8000_ATKHLD_WRITE(hw, ch, 0x7f7f);
	EMU8000_DCYSUS_WRITE(hw, ch, 0x7f7f);
	EMU8000_ENVVOL_WRITE(hw, ch, 0x8000);
	EMU8000_ATKHLDV_WRITE(hw, ch, 0x7f7f);
	/* decay/sustain parameter for volume envelope is used
	   for triggerg the voice */
	/* modulation envelope heights */
	EMU8000_PEFE_WRITE(hw, ch, 0x0);
	/* lfo1/2 delay */
	EMU8000_LFO1VAL_WRITE(hw, ch, 0x8000);
	EMU8000_LFO2VAL_WRITE(hw, ch, 0x8000);
	/* lfo1 pitch & cutoff shift */
	EMU8000_FMMOD_WRITE(hw, ch, 0);
	/* lfo1 volume & freq */
	EMU8000_TREMFRQ_WRITE(hw, ch, 0);
	/* lfo2 pitch & freq */
	EMU8000_FM2FRQ2_WRITE(hw, ch, 0);
	/* pan & loop start */
	temp = rec->panning[ch];
	temp = (temp <<24) | ((unsigned int)rec->loop_start[ch] - 1);
	EMU8000_PSST_WRITE(hw, ch, temp);
	/* chorus & loop end (chorus 8bit, MSB) */
	temp = 0; // chorus
	temp = (temp << 24) | ((unsigned int)rec->loop_start[ch] + rec->buf_size - 1);
	EMU8000_CSL_WRITE(hw, ch, temp);
	/* Q & current address (Q 4bit value, MSB) */
	temp = 0; // filterQ
	temp = (temp << 28) | ((unsigned int)rec->loop_start[ch] - 1);
	EMU8000_CCCA_WRITE(hw, ch, temp);
	/* clear unknown registers */
	EMU8000_00A0_WRITE(hw, ch, 0);
	EMU8000_0080_WRITE(hw, ch, 0);
}