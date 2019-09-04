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
struct snd_trident {TYPE_1__* card; int /*<<< orphan*/  pci; scalar_t__ in_suspend; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BANK_B_EN ; 
 unsigned int CENTEROUT ; 
 unsigned int COLD_RESET ; 
 int HZ ; 
 unsigned int LFEOUT ; 
 unsigned int PCMOUT ; 
 unsigned int SECONDARY_ID ; 
 int /*<<< orphan*/  SI_AC97_GPIO ; 
 int SI_AC97_PRIMARY_READY ; 
 int SI_AC97_SECONDARY_READY ; 
 int /*<<< orphan*/  SI_SERIAL_INTF_CTRL ; 
 unsigned int SURROUT ; 
 int /*<<< orphan*/  T4D_LFO_GC_CIR ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  do_delay (struct snd_trident*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_trident_sis_reset(struct snd_trident *trident)
{
	unsigned long end_time;
	unsigned int i;
	int r;

	r = trident->in_suspend ? 0 : 2;	/* count of retries */
      __si7018_retry:
	pci_write_config_byte(trident->pci, 0x46, 0x04);	/* SOFTWARE RESET */
	udelay(100);
	pci_write_config_byte(trident->pci, 0x46, 0x00);
	udelay(100);
	/* disable AC97 GPIO interrupt */
	outb(0x00, TRID_REG(trident, SI_AC97_GPIO));
	/* initialize serial interface, force cold reset */
	i = PCMOUT|SURROUT|CENTEROUT|LFEOUT|SECONDARY_ID|COLD_RESET;
	outl(i, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	udelay(1000);
	/* remove cold reset */
	i &= ~COLD_RESET;
	outl(i, TRID_REG(trident, SI_SERIAL_INTF_CTRL));
	udelay(2000);
	/* wait, until the codec is ready */
	end_time = (jiffies + (HZ * 3) / 4) + 1;
	do {
		if ((inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) & SI_AC97_PRIMARY_READY) != 0)
			goto __si7018_ok;
		do_delay(trident);
	} while (time_after_eq(end_time, jiffies));
	dev_err(trident->card->dev, "AC'97 codec ready error [0x%x]\n",
		inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)));
	if (r-- > 0) {
		end_time = jiffies + HZ;
		do {
			do_delay(trident);
		} while (time_after_eq(end_time, jiffies));
		goto __si7018_retry;
	}
      __si7018_ok:
	/* wait for the second codec */
	do {
		if ((inl(TRID_REG(trident, SI_SERIAL_INTF_CTRL)) & SI_AC97_SECONDARY_READY) != 0)
			break;
		do_delay(trident);
	} while (time_after_eq(end_time, jiffies));
	/* enable 64 channel mode */
	outl(BANK_B_EN, TRID_REG(trident, T4D_LFO_GC_CIR));
	return 0;
}