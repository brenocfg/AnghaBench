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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct advk_pcie {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PIO_ISR ; 
 int /*<<< orphan*/  PIO_START ; 
 int /*<<< orphan*/  PIO_TIMEOUT_MS ; 
 scalar_t__ advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int advk_pcie_wait_pio(struct advk_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	unsigned long timeout;

	timeout = jiffies + msecs_to_jiffies(PIO_TIMEOUT_MS);

	while (time_before(jiffies, timeout)) {
		u32 start, isr;

		start = advk_readl(pcie, PIO_START);
		isr = advk_readl(pcie, PIO_ISR);
		if (!start && isr)
			return 0;
	}

	dev_err(dev, "config read/write timed out\n");
	return -ETIMEDOUT;
}