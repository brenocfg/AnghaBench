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
struct TYPE_2__ {unsigned int policy_idx_hmask; int /*<<< orphan*/  xfrm_policy_lock; struct hlist_head* policy_byidx; } ;
struct net {TYPE_1__ xfrm; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct hlist_head* xfrm_hash_alloc (unsigned int) ; 
 int /*<<< orphan*/  xfrm_hash_free (struct hlist_head*,unsigned int) ; 
 int /*<<< orphan*/  xfrm_idx_hash_transfer (struct hlist_head*,struct hlist_head*,unsigned int) ; 
 unsigned int xfrm_new_hash_mask (unsigned int) ; 

__attribute__((used)) static void xfrm_byidx_resize(struct net *net, int total)
{
	unsigned int hmask = net->xfrm.policy_idx_hmask;
	unsigned int nhashmask = xfrm_new_hash_mask(hmask);
	unsigned int nsize = (nhashmask + 1) * sizeof(struct hlist_head);
	struct hlist_head *oidx = net->xfrm.policy_byidx;
	struct hlist_head *nidx = xfrm_hash_alloc(nsize);
	int i;

	if (!nidx)
		return;

	spin_lock_bh(&net->xfrm.xfrm_policy_lock);

	for (i = hmask; i >= 0; i--)
		xfrm_idx_hash_transfer(oidx + i, nidx, nhashmask);

	net->xfrm.policy_byidx = nidx;
	net->xfrm.policy_idx_hmask = nhashmask;

	spin_unlock_bh(&net->xfrm.xfrm_policy_lock);

	xfrm_hash_free(oidx, (hmask + 1) * sizeof(struct hlist_head));
}