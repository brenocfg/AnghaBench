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
struct dsp_spos_instance {int spdif_csuv_default; int /*<<< orphan*/  spdif_status_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_ASER_FADDR ; 
 int /*<<< orphan*/  DSP_SPDIF_STATUS_HW_ENABLED ; 
 int /*<<< orphan*/  SP_SPDOUT_CONTROL ; 
 int /*<<< orphan*/  SP_SPDOUT_CSUV ; 
 int SP_SPDOUT_FIFO ; 
 int /*<<< orphan*/  cs46xx_dsp_disable_spdif_hw (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  cs46xx_poke_via_dsp (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int cs46xx_dsp_enable_spdif_hw (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	/* if hw-ctrl already enabled, turn off to reset logic ... */
	cs46xx_dsp_disable_spdif_hw (chip);
	udelay(50);

	/* set SPDIF output FIFO slot */
	snd_cs46xx_pokeBA0(chip, BA0_ASER_FADDR, ( 0x8000 | ((SP_SPDOUT_FIFO >> 4) << 4) ));

	/* SPDIF output MASTER ENABLE */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CONTROL, 0x80000000);

	/* right and left validate bit */
	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdif_csuv_default);

	/* monitor state */
	ins->spdif_status_out |= DSP_SPDIF_STATUS_HW_ENABLED;

	return 0;
}