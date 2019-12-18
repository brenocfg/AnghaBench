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
struct snd_cs46xx {struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int /*<<< orphan*/  spdif_status_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_ASER_FADDR ; 
 int /*<<< orphan*/  DSP_SPDIF_STATUS_HW_ENABLED ; 
 int /*<<< orphan*/  SP_SPDIN_FIFOPTR ; 
 int /*<<< orphan*/  SP_SPDOUT_CONTROL ; 
 int /*<<< orphan*/  SP_SPDOUT_CSUV ; 
 int /*<<< orphan*/  cs46xx_poke_via_dsp (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs46xx_dsp_disable_spdif_hw (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* set SPDIF output FIFO slot */
	snd_cs46xx_pokeBA0(chip, BA0_ASER_FADDR, 0);

	/* SPDIF output MASTER ENABLE */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CONTROL, 0);

	/* right and left validate bit */
	/*cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdif_csuv_default);*/
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, 0x0);

	/* clear fifo pointer */
	cs46xx_poke_via_dsp (chip,SP_SPDIN_FIFOPTR, 0x0);

	/* monitor state */
	ins->spdif_status_out &= ~DSP_SPDIF_STATUS_HW_ENABLED;
}