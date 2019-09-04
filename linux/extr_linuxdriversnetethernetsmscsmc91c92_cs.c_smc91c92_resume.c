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
struct smc_private {scalar_t__ manfid; scalar_t__ cardid; } ;
struct pcmcia_device {scalar_t__ open; struct net_device* priv; } ;
struct net_device {int base_addr; } ;

/* Variables and functions */
 scalar_t__ MANFID_MEGAHERTZ ; 
 scalar_t__ MANFID_MOTOROLA ; 
 scalar_t__ MANFID_OSITECH ; 
 scalar_t__ MANFID_PSION ; 
 int OSITECH_AUI_PWR ; 
 int OSITECH_RESET_ISR ; 
 scalar_t__ PRODID_MEGAHERTZ_EM3288 ; 
 scalar_t__ PRODID_OSITECH_SEVEN ; 
 scalar_t__ PRODID_PSION_NET100 ; 
 int /*<<< orphan*/  mhz_3288_power (struct pcmcia_device*) ; 
 int /*<<< orphan*/  mot_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int osi_load_firmware (struct pcmcia_device*) ; 
 int /*<<< orphan*/  set_bits (int,int) ; 
 int /*<<< orphan*/  smc_reset (struct net_device*) ; 

__attribute__((used)) static int smc91c92_resume(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;
	struct smc_private *smc = netdev_priv(dev);
	int i;

	if ((smc->manfid == MANFID_MEGAHERTZ) &&
	    (smc->cardid == PRODID_MEGAHERTZ_EM3288))
		mhz_3288_power(link);
	if (smc->manfid == MANFID_MOTOROLA)
		mot_config(link);
	if ((smc->manfid == MANFID_OSITECH) &&
	    (smc->cardid != PRODID_OSITECH_SEVEN)) {
		/* Power up the card and enable interrupts */
		set_bits(0x0300, dev->base_addr-0x10+OSITECH_AUI_PWR);
		set_bits(0x0300, dev->base_addr-0x10+OSITECH_RESET_ISR);
	}
	if (((smc->manfid == MANFID_OSITECH) &&
	     (smc->cardid == PRODID_OSITECH_SEVEN)) ||
	    ((smc->manfid == MANFID_PSION) &&
	     (smc->cardid == PRODID_PSION_NET100))) {
		i = osi_load_firmware(link);
		if (i) {
			netdev_err(dev, "Failed to load firmware\n");
			return i;
		}
	}
	if (link->open) {
		smc_reset(dev);
		netif_device_attach(dev);
	}

	return 0;
}