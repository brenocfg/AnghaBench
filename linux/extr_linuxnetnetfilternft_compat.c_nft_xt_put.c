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
struct nft_xt {scalar_t__ refcnt; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct nft_xt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static bool nft_xt_put(struct nft_xt *xt)
{
	if (--xt->refcnt == 0) {
		list_del(&xt->head);
		kfree_rcu(xt, rcu_head);
		return true;
	}

	return false;
}