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
typedef  int u16 ;
struct device {int dummy; } ;
struct altera_pcie {int /*<<< orphan*/  root_bus_nr; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ LINK_RETRAIN_TIMEOUT ; 
 scalar_t__ LINK_UP_TIMEOUT ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_LT ; 
 int /*<<< orphan*/  RP_DEVFN ; 
 scalar_t__ altera_pcie_link_up (struct altera_pcie*) ; 
 int /*<<< orphan*/  altera_read_cap_word (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void altera_wait_link_retrain(struct altera_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	u16 reg16;
	unsigned long start_jiffies;

	/* Wait for link training end. */
	start_jiffies = jiffies;
	for (;;) {
		altera_read_cap_word(pcie, pcie->root_bus_nr, RP_DEVFN,
				     PCI_EXP_LNKSTA, &reg16);
		if (!(reg16 & PCI_EXP_LNKSTA_LT))
			break;

		if (time_after(jiffies, start_jiffies + LINK_RETRAIN_TIMEOUT)) {
			dev_err(dev, "link retrain timeout\n");
			break;
		}
		udelay(100);
	}

	/* Wait for link is up */
	start_jiffies = jiffies;
	for (;;) {
		if (altera_pcie_link_up(pcie))
			break;

		if (time_after(jiffies, start_jiffies + LINK_UP_TIMEOUT)) {
			dev_err(dev, "link up timeout\n");
			break;
		}
		udelay(100);
	}
}