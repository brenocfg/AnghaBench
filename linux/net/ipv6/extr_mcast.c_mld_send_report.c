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
struct ifmcaddr6 {int mca_flags; int /*<<< orphan*/  mca_lock; scalar_t__* mca_sfcount; struct ifmcaddr6* next; } ;

/* Variables and functions */
 int MAF_NOREPORT ; 
 size_t MCAST_EXCLUDE ; 
 int MLD2_MODE_IS_EXCLUDE ; 
 int MLD2_MODE_IS_INCLUDE ; 
 struct sk_buff* add_grec (struct sk_buff*,struct ifmcaddr6*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mld_sendpack (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mld_send_report(struct inet6_dev *idev, struct ifmcaddr6 *pmc)
{
	struct sk_buff *skb = NULL;
	int type;

	read_lock_bh(&idev->lock);
	if (!pmc) {
		for (pmc = idev->mc_list; pmc; pmc = pmc->next) {
			if (pmc->mca_flags & MAF_NOREPORT)
				continue;
			spin_lock_bh(&pmc->mca_lock);
			if (pmc->mca_sfcount[MCAST_EXCLUDE])
				type = MLD2_MODE_IS_EXCLUDE;
			else
				type = MLD2_MODE_IS_INCLUDE;
			skb = add_grec(skb, pmc, type, 0, 0, 0);
			spin_unlock_bh(&pmc->mca_lock);
		}
	} else {
		spin_lock_bh(&pmc->mca_lock);
		if (pmc->mca_sfcount[MCAST_EXCLUDE])
			type = MLD2_MODE_IS_EXCLUDE;
		else
			type = MLD2_MODE_IS_INCLUDE;
		skb = add_grec(skb, pmc, type, 0, 0, 0);
		spin_unlock_bh(&pmc->mca_lock);
	}
	read_unlock_bh(&idev->lock);
	if (skb)
		mld_sendpack(skb);
}