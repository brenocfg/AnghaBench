#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int entries_dmaaddr; int /*<<< orphan*/ * entries; } ;
struct snd_trident {int ac97_ctrl; unsigned int spdif_bits; int /*<<< orphan*/  spdif_ctrl; TYPE_2__ tlb; TYPE_1__* card; struct pci_dev* pci; } ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 scalar_t__ NX_ACR0_AC97_COM_STAT ; 
 unsigned int NX_SB_IRQ_DISABLE ; 
 scalar_t__ NX_SPCSTATUS ; 
 scalar_t__ NX_SPCTRL_SPCSO ; 
 scalar_t__ NX_TLBC ; 
 scalar_t__ T4D_MISCINT ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  do_delay (struct snd_trident*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_trident_stop_all_voices (struct snd_trident*) ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_trident_4d_nx_init(struct snd_trident *trident)
{
	struct pci_dev *pci = trident->pci;
	unsigned long end_time;

	/* reset the legacy configuration and whole audio/wavetable block */
	pci_write_config_dword(pci, 0x40, 0);	/* DDMA */
	pci_write_config_byte(pci, 0x44, 0);	/* ports */
	pci_write_config_byte(pci, 0x45, 0);	/* Legacy DMA */

	pci_write_config_byte(pci, 0x46, 1); /* reset */
	udelay(100);
	pci_write_config_byte(pci, 0x46, 0); /* release reset */
	udelay(100);

	/* warm reset of the AC'97 codec */
	outl(0x00000001, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	udelay(100);
	outl(0x00000000, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	/* wait, until the codec is ready */
	end_time = (jiffies + (HZ * 3) / 4) + 1;
	do {
		if ((inl(TRID_REG(trident, NX_ACR0_AC97_COM_STAT)) & 0x0008) != 0)
			goto __nx_ok;
		do_delay(trident);
	} while (time_after_eq(end_time, jiffies));
	dev_err(trident->card->dev, "AC'97 codec ready error [0x%x]\n",
		inl(TRID_REG(trident, NX_ACR0_AC97_COM_STAT)));
	return -EIO;

 __nx_ok:
	/* DAC on */
	trident->ac97_ctrl = 0x00000002;
	outl(trident->ac97_ctrl, TRID_REG(trident, NX_ACR0_AC97_COM_STAT));
	/* disable SB IRQ */
	outl(NX_SB_IRQ_DISABLE, TRID_REG(trident, T4D_MISCINT));

	snd_trident_stop_all_voices(trident);

	if (trident->tlb.entries != NULL) {
		unsigned int i;
		/* enable virtual addressing via TLB */
		i = trident->tlb.entries_dmaaddr;
		i |= 0x00000001;
		outl(i, TRID_REG(trident, NX_TLBC));
	} else {
		outl(0, TRID_REG(trident, NX_TLBC));
	}
	/* initialize S/PDIF */
	outl(trident->spdif_bits, TRID_REG(trident, NX_SPCSTATUS));
	outb(trident->spdif_ctrl, TRID_REG(trident, NX_SPCTRL_SPCSO + 3));

	return 0;
}