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
struct nlattr {int dummy; } ;
struct nft_set_desc {int dummy; } ;
struct nft_set {int flags; } ;
struct nft_rbtree {int /*<<< orphan*/  gc_work; int /*<<< orphan*/  root; int /*<<< orphan*/  count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NFT_SET_TIMEOUT ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  nft_rbtree_gc ; 
 int /*<<< orphan*/  nft_set_gc_interval (struct nft_set const*) ; 
 struct nft_rbtree* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqcount_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int nft_rbtree_init(const struct nft_set *set,
			   const struct nft_set_desc *desc,
			   const struct nlattr * const nla[])
{
	struct nft_rbtree *priv = nft_set_priv(set);

	rwlock_init(&priv->lock);
	seqcount_init(&priv->count);
	priv->root = RB_ROOT;

	INIT_DEFERRABLE_WORK(&priv->gc_work, nft_rbtree_gc);
	if (set->flags & NFT_SET_TIMEOUT)
		queue_delayed_work(system_power_efficient_wq, &priv->gc_work,
				   nft_set_gc_interval(set));

	return 0;
}