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
typedef  int u_short ;
struct pcmcia_device {TYPE_1__** resource; struct net_device* priv; } ;
struct net_device {unsigned int base_addr; } ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 scalar_t__ BASE_ADDR ; 
 int CFG_16BIT ; 
 scalar_t__ CONFIG ; 
 scalar_t__ CONTROL ; 
 int ENODEV ; 
 scalar_t__ IO_DATA_PATH_WIDTH_AUTO ; 
 scalar_t__ REVISION ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_fixup_iowidth (struct pcmcia_device*) ; 
 int /*<<< orphan*/  smc91c92_resume (struct pcmcia_device*) ; 
 int /*<<< orphan*/  smc91c92_suspend (struct pcmcia_device*) ; 

__attribute__((used)) static int check_sig(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    unsigned int ioaddr = dev->base_addr;
    int width;
    u_short s;

    SMC_SELECT_BANK(1);
    if (inw(ioaddr + BANK_SELECT) >> 8 != 0x33) {
	/* Try powering up the chip */
	outw(0, ioaddr + CONTROL);
	mdelay(55);
    }

    /* Try setting bus width */
    width = (link->resource[0]->flags == IO_DATA_PATH_WIDTH_AUTO);
    s = inb(ioaddr + CONFIG);
    if (width)
	s |= CFG_16BIT;
    else
	s &= ~CFG_16BIT;
    outb(s, ioaddr + CONFIG);

    /* Check Base Address Register to make sure bus width is OK */
    s = inw(ioaddr + BASE_ADDR);
    if ((inw(ioaddr + BANK_SELECT) >> 8 == 0x33) &&
	((s >> 8) != (s & 0xff))) {
	SMC_SELECT_BANK(3);
	s = inw(ioaddr + REVISION);
	return s & 0xff;
    }

    if (width) {
	    netdev_info(dev, "using 8-bit IO window\n");

	    smc91c92_suspend(link);
	    pcmcia_fixup_iowidth(link);
	    smc91c92_resume(link);
	    return check_sig(link);
    }
    return -ENODEV;
}