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
struct device {int dummy; } ;
struct advk_pcie {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int LINK_WAIT_MAX_RETRIES ; 
 int /*<<< orphan*/  LINK_WAIT_USLEEP_MAX ; 
 int /*<<< orphan*/  LINK_WAIT_USLEEP_MIN ; 
 scalar_t__ advk_pcie_link_up (struct advk_pcie*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advk_pcie_wait_for_link(struct advk_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	int retries;

	/* check if the link is up or not */
	for (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) {
		if (advk_pcie_link_up(pcie)) {
			dev_info(dev, "link up\n");
			return 0;
		}

		usleep_range(LINK_WAIT_USLEEP_MIN, LINK_WAIT_USLEEP_MAX);
	}

	dev_err(dev, "link never came up\n");
	return -ETIMEDOUT;
}