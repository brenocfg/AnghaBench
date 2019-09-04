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
typedef  int u32 ;
struct TYPE_2__ {int revision; } ;
struct ssb_device {TYPE_1__ id; struct ssb_bus* bus; } ;
struct ssb_chipcommon {int capabilities; struct ssb_device* dev; } ;
struct ssb_bus {int dummy; } ;
typedef  enum ssb_clkmode { ____Placeholder_ssb_clkmode } ssb_clkmode ;

/* Variables and functions */
 int SSB_CHIPCO_CAP_PCTL ; 
 int SSB_CHIPCO_CAP_PMU ; 
 int /*<<< orphan*/  SSB_CHIPCO_SLOWCLKCTL ; 
 int SSB_CHIPCO_SLOWCLKCTL_ENXTAL ; 
 int SSB_CHIPCO_SLOWCLKCTL_FSLOW ; 
 int SSB_CHIPCO_SLOWCLKCTL_IPLL ; 
 int SSB_CHIPCO_SLOWCLKCTL_SRC ; 
 int SSB_CHIPCO_SLOWCLKCTL_SRC_XTAL ; 
 int /*<<< orphan*/  SSB_CHIPCO_SYSCLKCTL ; 
 int SSB_CHIPCO_SYSCLKCTL_FORCEHT ; 
#define  SSB_CLKMODE_DYNAMIC 130 
#define  SSB_CLKMODE_FAST 129 
#define  SSB_CLKMODE_SLOW 128 
 int /*<<< orphan*/  SSB_GPIO_XTAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssb_pci_xtal (struct ssb_bus*,int /*<<< orphan*/ ,int) ; 

void ssb_chipco_set_clockmode(struct ssb_chipcommon *cc,
			      enum ssb_clkmode mode)
{
	struct ssb_device *ccdev = cc->dev;
	struct ssb_bus *bus;
	u32 tmp;

	if (!ccdev)
		return;
	bus = ccdev->bus;

	/* We support SLOW only on 6..9 */
	if (ccdev->id.revision >= 10 && mode == SSB_CLKMODE_SLOW)
		mode = SSB_CLKMODE_DYNAMIC;

	if (cc->capabilities & SSB_CHIPCO_CAP_PMU)
		return; /* PMU controls clockmode, separated function needed */
	WARN_ON(ccdev->id.revision >= 20);

	/* chipcommon cores prior to rev6 don't support dynamic clock control */
	if (ccdev->id.revision < 6)
		return;

	/* ChipCommon cores rev10+ need testing */
	if (ccdev->id.revision >= 10)
		return;

	if (!(cc->capabilities & SSB_CHIPCO_CAP_PCTL))
		return;

	switch (mode) {
	case SSB_CLKMODE_SLOW: /* For revs 6..9 only */
		tmp = chipco_read32(cc, SSB_CHIPCO_SLOWCLKCTL);
		tmp |= SSB_CHIPCO_SLOWCLKCTL_FSLOW;
		chipco_write32(cc, SSB_CHIPCO_SLOWCLKCTL, tmp);
		break;
	case SSB_CLKMODE_FAST:
		if (ccdev->id.revision < 10) {
			ssb_pci_xtal(bus, SSB_GPIO_XTAL, 1); /* Force crystal on */
			tmp = chipco_read32(cc, SSB_CHIPCO_SLOWCLKCTL);
			tmp &= ~SSB_CHIPCO_SLOWCLKCTL_FSLOW;
			tmp |= SSB_CHIPCO_SLOWCLKCTL_IPLL;
			chipco_write32(cc, SSB_CHIPCO_SLOWCLKCTL, tmp);
		} else {
			chipco_write32(cc, SSB_CHIPCO_SYSCLKCTL,
				(chipco_read32(cc, SSB_CHIPCO_SYSCLKCTL) |
				 SSB_CHIPCO_SYSCLKCTL_FORCEHT));
			/* udelay(150); TODO: not available in early init */
		}
		break;
	case SSB_CLKMODE_DYNAMIC:
		if (ccdev->id.revision < 10) {
			tmp = chipco_read32(cc, SSB_CHIPCO_SLOWCLKCTL);
			tmp &= ~SSB_CHIPCO_SLOWCLKCTL_FSLOW;
			tmp &= ~SSB_CHIPCO_SLOWCLKCTL_IPLL;
			tmp &= ~SSB_CHIPCO_SLOWCLKCTL_ENXTAL;
			if ((tmp & SSB_CHIPCO_SLOWCLKCTL_SRC) !=
			    SSB_CHIPCO_SLOWCLKCTL_SRC_XTAL)
				tmp |= SSB_CHIPCO_SLOWCLKCTL_ENXTAL;
			chipco_write32(cc, SSB_CHIPCO_SLOWCLKCTL, tmp);

			/* For dynamic control, we have to release our xtal_pu
			 * "force on" */
			if (tmp & SSB_CHIPCO_SLOWCLKCTL_ENXTAL)
				ssb_pci_xtal(bus, SSB_GPIO_XTAL, 0);
		} else {
			chipco_write32(cc, SSB_CHIPCO_SYSCLKCTL,
				(chipco_read32(cc, SSB_CHIPCO_SYSCLKCTL) &
				 ~SSB_CHIPCO_SYSCLKCTL_FORCEHT));
		}
		break;
	default:
		WARN_ON(1);
	}
}