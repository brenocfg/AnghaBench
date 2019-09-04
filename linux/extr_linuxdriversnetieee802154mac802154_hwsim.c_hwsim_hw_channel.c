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
typedef  void* u8 ;
struct ieee802154_hw {struct hwsim_phy* priv; } ;
struct hwsim_pib {void* channel; void* page; } ;
struct hwsim_phy {int /*<<< orphan*/  pib; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree_rcu (struct hwsim_pib*,int /*<<< orphan*/ ) ; 
 struct hwsim_pib* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct hwsim_pib*) ; 
 struct hwsim_pib* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwsim_hw_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct hwsim_phy *phy = hw->priv;
	struct hwsim_pib *pib, *pib_old;

	pib = kzalloc(sizeof(*pib), GFP_KERNEL);
	if (!pib)
		return -ENOMEM;

	pib->page = page;
	pib->channel = channel;

	pib_old = rtnl_dereference(phy->pib);
	rcu_assign_pointer(phy->pib, pib);
	kfree_rcu(pib_old, rcu);
	return 0;
}