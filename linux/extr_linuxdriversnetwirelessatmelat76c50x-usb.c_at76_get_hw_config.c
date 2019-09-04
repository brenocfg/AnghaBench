#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  regulatory_domain; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  regulatory_domain; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  regulatory_domain; int /*<<< orphan*/  mac_addr; } ;
union at76_hwcfg {TYPE_3__ r5; TYPE_2__ r3; TYPE_1__ i; } ;
struct at76_priv {TYPE_4__* hw; int /*<<< orphan*/  regulatory_domain; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  udev; int /*<<< orphan*/  board_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int at76_get_hw_cfg (int /*<<< orphan*/ ,union at76_hwcfg*,int) ; 
 int at76_get_hw_cfg_intersil (int /*<<< orphan*/ ,union at76_hwcfg*,int) ; 
 scalar_t__ at76_is_503rfmd (int /*<<< orphan*/ ) ; 
 scalar_t__ at76_is_intersil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union at76_hwcfg*) ; 
 union at76_hwcfg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int at76_get_hw_config(struct at76_priv *priv)
{
	int ret;
	union at76_hwcfg *hwcfg = kmalloc(sizeof(*hwcfg), GFP_KERNEL);

	if (!hwcfg)
		return -ENOMEM;

	if (at76_is_intersil(priv->board_type)) {
		ret = at76_get_hw_cfg_intersil(priv->udev, hwcfg,
					       sizeof(hwcfg->i));
		if (ret < 0)
			goto exit;
		memcpy(priv->mac_addr, hwcfg->i.mac_addr, ETH_ALEN);
		priv->regulatory_domain = hwcfg->i.regulatory_domain;
	} else if (at76_is_503rfmd(priv->board_type)) {
		ret = at76_get_hw_cfg(priv->udev, hwcfg, sizeof(hwcfg->r3));
		if (ret < 0)
			goto exit;
		memcpy(priv->mac_addr, hwcfg->r3.mac_addr, ETH_ALEN);
		priv->regulatory_domain = hwcfg->r3.regulatory_domain;
	} else {
		ret = at76_get_hw_cfg(priv->udev, hwcfg, sizeof(hwcfg->r5));
		if (ret < 0)
			goto exit;
		memcpy(priv->mac_addr, hwcfg->r5.mac_addr, ETH_ALEN);
		priv->regulatory_domain = hwcfg->r5.regulatory_domain;
	}

exit:
	kfree(hwcfg);
	if (ret < 0)
		wiphy_err(priv->hw->wiphy, "cannot get HW Config (error %d)\n",
			  ret);

	return ret;
}