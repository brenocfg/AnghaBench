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
struct snd_msnd {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDEXAR_AUX_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_IN_SET_POTS ; 
 int /*<<< orphan*/  HDEXAR_MIC_SET_POTS ; 
 int /*<<< orphan*/  MSND_MIXER_AUX ; 
 int /*<<< orphan*/  MSND_MIXER_IMIX ; 
 int /*<<< orphan*/  MSND_MIXER_LINE ; 
 int /*<<< orphan*/  MSND_MIXER_MIC ; 
 int /*<<< orphan*/  MSND_MIXER_PCM ; 
 int /*<<< orphan*/  MSND_MIXER_SYNTH ; 
 int /*<<< orphan*/  bAuxPotPos ; 
 int /*<<< orphan*/  bInPotPos ; 
 int /*<<< orphan*/  bMicPotPos ; 
 scalar_t__ msndPinnacle ; 
 int /*<<< orphan*/  update_pot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_potm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_volm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wCurrInVol ; 
 int /*<<< orphan*/  wCurrMHdrVol ; 
 int /*<<< orphan*/  wCurrPlayVol ; 

void snd_msndmix_setup(struct snd_msnd *dev)
{
	update_pot(MSND_MIXER_LINE, bInPotPos, HDEXAR_IN_SET_POTS);
	update_potm(MSND_MIXER_AUX, bAuxPotPos, HDEXAR_AUX_SET_POTS);
	update_volm(MSND_MIXER_PCM, wCurrPlayVol);
	update_volm(MSND_MIXER_IMIX, wCurrInVol);
	if (dev->type == msndPinnacle) {
		update_pot(MSND_MIXER_MIC, bMicPotPos, HDEXAR_MIC_SET_POTS);
		update_volm(MSND_MIXER_SYNTH, wCurrMHdrVol);
	}
}