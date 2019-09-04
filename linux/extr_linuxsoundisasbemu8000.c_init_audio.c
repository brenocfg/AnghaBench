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
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_ATKHLDV_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_ATKHLD_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_CCCA_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int EMU8000_CHANNELS ; 
 int /*<<< orphan*/  EMU8000_CPF_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_CSL_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_CVCF_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  EMU8000_DCYSUS_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_ENVVAL_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_ENVVOL_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_FM2FRQ2_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_FMMOD_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_IFATN_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_IP_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_LFO1VAL_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_LFO2VAL_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_PEFE_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_PSST_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_PTRX_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_TREMFRQ_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_VTFT_WRITE (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_audio(struct snd_emu8000 *emu)
{
	int ch;

	/* turn off envelope engines */
	for (ch = 0; ch < EMU8000_CHANNELS; ch++)
		EMU8000_DCYSUSV_WRITE(emu, ch, 0x80);
  
	/* reset all other parameters to zero */
	for (ch = 0; ch < EMU8000_CHANNELS; ch++) {
		EMU8000_ENVVOL_WRITE(emu, ch, 0);
		EMU8000_ENVVAL_WRITE(emu, ch, 0);
		EMU8000_DCYSUS_WRITE(emu, ch, 0);
		EMU8000_ATKHLDV_WRITE(emu, ch, 0);
		EMU8000_LFO1VAL_WRITE(emu, ch, 0);
		EMU8000_ATKHLD_WRITE(emu, ch, 0);
		EMU8000_LFO2VAL_WRITE(emu, ch, 0);
		EMU8000_IP_WRITE(emu, ch, 0);
		EMU8000_IFATN_WRITE(emu, ch, 0);
		EMU8000_PEFE_WRITE(emu, ch, 0);
		EMU8000_FMMOD_WRITE(emu, ch, 0);
		EMU8000_TREMFRQ_WRITE(emu, ch, 0);
		EMU8000_FM2FRQ2_WRITE(emu, ch, 0);
		EMU8000_PTRX_WRITE(emu, ch, 0);
		EMU8000_VTFT_WRITE(emu, ch, 0);
		EMU8000_PSST_WRITE(emu, ch, 0);
		EMU8000_CSL_WRITE(emu, ch, 0);
		EMU8000_CCCA_WRITE(emu, ch, 0);
	}

	for (ch = 0; ch < EMU8000_CHANNELS; ch++) {
		EMU8000_CPF_WRITE(emu, ch, 0);
		EMU8000_CVCF_WRITE(emu, ch, 0);
	}
}