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
struct snd_trident_voice {unsigned int Pan; int number; int GVSel; } ;
struct snd_trident {int dummy; } ;

/* Variables and functions */
 scalar_t__ CH_GVSEL_PAN_VOL_CTRL_EC ; 
 scalar_t__ T4D_LFO_GC_CIR ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,scalar_t__) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_trident_write_pan_reg(struct snd_trident * trident,
				      struct snd_trident_voice * voice,
				      unsigned int Pan)
{
	voice->Pan = Pan;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	outb(((voice->GVSel & 0x01) << 7) | (voice->Pan & 0x7f),
	     TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC + 3));
}