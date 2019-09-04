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
struct snd_trident_voice {unsigned int Vol; int number; int CTRL; } ;
struct snd_trident {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_GVSEL_PAN_VOL_CTRL_EC ; 
 int /*<<< orphan*/  T4D_LFO_GC_CIR ; 
#define  TRIDENT_DEVICE_ID_DX 130 
#define  TRIDENT_DEVICE_ID_NX 129 
#define  TRIDENT_DEVICE_ID_SI7018 128 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_trident_write_vol_reg(struct snd_trident * trident,
				      struct snd_trident_voice * voice,
				      unsigned int Vol)
{
	voice->Vol = Vol;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	switch (trident->device) {
	case TRIDENT_DEVICE_ID_DX:
	case TRIDENT_DEVICE_ID_NX:
		outb(voice->Vol >> 2, TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC + 2));
		break;
	case TRIDENT_DEVICE_ID_SI7018:
		/* dev_dbg(trident->card->dev, "voice->Vol = 0x%x\n", voice->Vol); */
		outw((voice->CTRL << 12) | voice->Vol,
		     TRID_REG(trident, CH_GVSEL_PAN_VOL_CTRL_EC));
		break;
	}
}