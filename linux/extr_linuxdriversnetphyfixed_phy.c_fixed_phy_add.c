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
struct fixed_phy_status {int dummy; } ;
struct fixed_phy {int addr; int link_gpio; int /*<<< orphan*/  node; struct fixed_phy_status status; int /*<<< orphan*/  seqcount; } ;
struct fixed_mdio_bus {int /*<<< orphan*/  phys; TYPE_1__* mii_bus; } ;
struct TYPE_2__ {unsigned int* irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_DIR_IN ; 
 unsigned int PHY_POLL ; 
 int /*<<< orphan*/  fixed_phy_update (struct fixed_phy*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int gpio_request_one (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct fixed_phy*) ; 
 struct fixed_phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct fixed_mdio_bus platform_fmb ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int swphy_validate_state (struct fixed_phy_status*) ; 

int fixed_phy_add(unsigned int irq, int phy_addr,
		  struct fixed_phy_status *status,
		  int link_gpio)
{
	int ret;
	struct fixed_mdio_bus *fmb = &platform_fmb;
	struct fixed_phy *fp;

	ret = swphy_validate_state(status);
	if (ret < 0)
		return ret;

	fp = kzalloc(sizeof(*fp), GFP_KERNEL);
	if (!fp)
		return -ENOMEM;

	seqcount_init(&fp->seqcount);

	if (irq != PHY_POLL)
		fmb->mii_bus->irq[phy_addr] = irq;

	fp->addr = phy_addr;
	fp->status = *status;
	fp->link_gpio = link_gpio;

	if (gpio_is_valid(fp->link_gpio)) {
		ret = gpio_request_one(fp->link_gpio, GPIOF_DIR_IN,
				       "fixed-link-gpio-link");
		if (ret)
			goto err_regs;
	}

	fixed_phy_update(fp);

	list_add_tail(&fp->node, &fmb->phys);

	return 0;

err_regs:
	kfree(fp);
	return ret;
}