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
struct sk_buff {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; } ;
struct ifmcaddr6 {int /*<<< orphan*/  mca_lock; scalar_t__* mca_sfcount; struct ifmcaddr6* next; } ;

/* Variables and functions */
 size_t MCAST_EXCLUDE ; 
 int MLD2_ALLOW_NEW_SOURCES ; 
 int MLD2_CHANGE_TO_EXCLUDE ; 
 struct sk_buff* add_grec (struct sk_buff*,struct ifmcaddr6*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mld_in_v1_mode (struct inet6_dev*) ; 
 int /*<<< orphan*/  mld_sendpack (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mld_send_initial_cr(struct inet6_dev *idev)
{
	struct sk_buff *skb;
	struct ifmcaddr6 *pmc;
	int type;

	if (mld_in_v1_mode(idev))
		return;

	skb = NULL;
	read_lock_bh(&idev->lock);
	for (pmc = idev->mc_list; pmc; pmc = pmc->next) {
		spin_lock_bh(&pmc->mca_lock);
		if (pmc->mca_sfcount[MCAST_EXCLUDE])
			type = MLD2_CHANGE_TO_EXCLUDE;
		else
			type = MLD2_ALLOW_NEW_SOURCES;
		skb = add_grec(skb, pmc, type, 0, 0, 1);
		spin_unlock_bh(&pmc->mca_lock);
	}
	read_unlock_bh(&idev->lock);
	if (skb)
		mld_sendpack(skb);
}