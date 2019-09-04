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
struct ahc_softc {int seltime; int seltime_b; int /*<<< orphan*/  flags; TYPE_1__* platform_data; } ;
struct ahc_platform_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_DISABLE_PCI_PERR ; 
 int /*<<< orphan*/  AHC_LINUX_NOIRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ahc_lockinit (struct ahc_softc*) ; 
 scalar_t__ aic7xxx_pci_parity ; 
 int aic7xxx_seltime ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

int
ahc_platform_alloc(struct ahc_softc *ahc, void *platform_arg)
{

	ahc->platform_data =
	    kzalloc(sizeof(struct ahc_platform_data), GFP_ATOMIC);
	if (ahc->platform_data == NULL)
		return (ENOMEM);
	ahc->platform_data->irq = AHC_LINUX_NOIRQ;
	ahc_lockinit(ahc);
	ahc->seltime = (aic7xxx_seltime & 0x3) << 4;
	ahc->seltime_b = (aic7xxx_seltime & 0x3) << 4;
	if (aic7xxx_pci_parity == 0)
		ahc->flags |= AHC_DISABLE_PCI_PERR;

	return (0);
}