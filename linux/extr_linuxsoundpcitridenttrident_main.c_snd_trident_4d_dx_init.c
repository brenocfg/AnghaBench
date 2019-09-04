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
struct snd_trident {int ac97_ctrl; TYPE_1__* card; struct pci_dev* pci; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DX_ACR2_AC97_COM_STAT ; 
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_delay (struct snd_trident*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_trident_stop_all_voices (struct snd_trident*) ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_trident_4d_dx_init(struct snd_trident *trident)
{
	struct pci_dev *pci = trident->pci;
	unsigned long end_time;

	/* reset the legacy configuration and whole audio/wavetable block */
	pci_write_config_dword(pci, 0x40, 0);	/* DDMA */
	pci_write_config_byte(pci, 0x44, 0);	/* ports */
	pci_write_config_byte(pci, 0x45, 0);	/* Legacy DMA */
	pci_write_config_byte(pci, 0x46, 4); /* reset */
	udelay(100);
	pci_write_config_byte(pci, 0x46, 0); /* release reset */
	udelay(100);
	
	/* warm reset of the AC'97 codec */
	outl(0x00000001, TRID_REG(trident, DX_ACR2_AC97_COM_STAT));
	udelay(100);
	outl(0x00000000, TRID_REG(trident, DX_ACR2_AC97_COM_STAT));
	/* DAC on, disable SB IRQ and try to force ADC valid signal */
	trident->ac97_ctrl = 0x0000004a;
	outl(trident->ac97_ctrl, TRID_REG(trident, DX_ACR2_AC97_COM_STAT));
	/* wait, until the codec is ready */
	end_time = (jiffies + (HZ * 3) / 4) + 1;
	do {
		if ((inl(TRID_REG(trident, DX_ACR2_AC97_COM_STAT)) & 0x0010) != 0)
			goto __dx_ok;
		do_delay(trident);
	} while (time_after_eq(end_time, jiffies));
	dev_err(trident->card->dev, "AC'97 codec ready error\n");
	return -EIO;

 __dx_ok:
	snd_trident_stop_all_voices(trident);

	return 0;
}