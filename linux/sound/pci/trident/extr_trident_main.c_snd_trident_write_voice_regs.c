#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_trident_voice {unsigned int LBA; int GVSel; int Pan; int CTRL; int FMC; int RVol; int CVol; int number; int Vol; int EC; int CSO; int Alpha; int FMS; int ESO; int Delta; int Attribute; } ;
struct snd_trident {int device; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CH_START ; 
 scalar_t__ T4D_LFO_GC_CIR ; 
#define  TRIDENT_DEVICE_ID_DX 130 
#define  TRIDENT_DEVICE_ID_NX 129 
#define  TRIDENT_DEVICE_ID_SI7018 128 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 

void snd_trident_write_voice_regs(struct snd_trident * trident,
				  struct snd_trident_voice * voice)
{
	unsigned int FmcRvolCvol;
	unsigned int regs[5];

	regs[1] = voice->LBA;
	regs[4] = (voice->GVSel << 31) |
		  ((voice->Pan & 0x0000007f) << 24) |
		  ((voice->CTRL & 0x0000000f) << 12);
	FmcRvolCvol = ((voice->FMC & 3) << 14) |
	              ((voice->RVol & 0x7f) << 7) |
	              (voice->CVol & 0x7f);

	switch (trident->device) {
	case TRIDENT_DEVICE_ID_SI7018:
		regs[4] |= voice->number > 31 ?
				(voice->Vol & 0x000003ff) :
				((voice->Vol & 0x00003fc) << (16-2)) |
				(voice->EC & 0x00000fff);
		regs[0] = (voice->CSO << 16) | ((voice->Alpha & 0x00000fff) << 4) |
			(voice->FMS & 0x0000000f);
		regs[2] = (voice->ESO << 16) | (voice->Delta & 0x0ffff);
		regs[3] = (voice->Attribute << 16) | FmcRvolCvol;
		break;
	case TRIDENT_DEVICE_ID_DX:
		regs[4] |= ((voice->Vol & 0x000003fc) << (16-2)) |
			   (voice->EC & 0x00000fff);
		regs[0] = (voice->CSO << 16) | ((voice->Alpha & 0x00000fff) << 4) |
			(voice->FMS & 0x0000000f);
		regs[2] = (voice->ESO << 16) | (voice->Delta & 0x0ffff);
		regs[3] = FmcRvolCvol;
		break;
	case TRIDENT_DEVICE_ID_NX:
		regs[4] |= ((voice->Vol & 0x000003fc) << (16-2)) |
			   (voice->EC & 0x00000fff);
		regs[0] = (voice->Delta << 24) | (voice->CSO & 0x00ffffff);
		regs[2] = ((voice->Delta << 16) & 0xff000000) |
			(voice->ESO & 0x00ffffff);
		regs[3] = (voice->Alpha << 20) |
			((voice->FMS & 0x0000000f) << 16) | FmcRvolCvol;
		break;
	default:
		snd_BUG();
		return;
	}

	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	outl(regs[0], TRID_REG(trident, CH_START + 0));
	outl(regs[1], TRID_REG(trident, CH_START + 4));
	outl(regs[2], TRID_REG(trident, CH_START + 8));
	outl(regs[3], TRID_REG(trident, CH_START + 12));
	outl(regs[4], TRID_REG(trident, CH_START + 16));

#if 0
	dev_dbg(trident->card->dev, "written %i channel:\n", voice->number);
	dev_dbg(trident->card->dev, "  regs[0] = 0x%x/0x%x\n",
	       regs[0], inl(TRID_REG(trident, CH_START + 0)));
	dev_dbg(trident->card->dev, "  regs[1] = 0x%x/0x%x\n",
	       regs[1], inl(TRID_REG(trident, CH_START + 4)));
	dev_dbg(trident->card->dev, "  regs[2] = 0x%x/0x%x\n",
	       regs[2], inl(TRID_REG(trident, CH_START + 8)));
	dev_dbg(trident->card->dev, "  regs[3] = 0x%x/0x%x\n",
	       regs[3], inl(TRID_REG(trident, CH_START + 12)));
	dev_dbg(trident->card->dev, "  regs[4] = 0x%x/0x%x\n",
	       regs[4], inl(TRID_REG(trident, CH_START + 16)));
#endif
}