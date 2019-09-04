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
struct nwl_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int LINK_WAIT_MAX_RETRIES ; 
 int /*<<< orphan*/  LINK_WAIT_USLEEP_MAX ; 
 int /*<<< orphan*/  LINK_WAIT_USLEEP_MIN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ nwl_phy_link_up (struct nwl_pcie*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nwl_wait_for_link(struct nwl_pcie *pcie)
{
	struct device *dev = pcie->dev;
	int retries;

	/* check if the link is up or not */
	for (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) {
		if (nwl_phy_link_up(pcie))
			return 0;
		usleep_range(LINK_WAIT_USLEEP_MIN, LINK_WAIT_USLEEP_MAX);
	}

	dev_err(dev, "PHY link never came up\n");
	return -ETIMEDOUT;
}