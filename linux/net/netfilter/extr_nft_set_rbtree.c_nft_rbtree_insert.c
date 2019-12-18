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
struct nft_set_ext {int dummy; } ;
struct nft_set_elem {struct nft_rbtree_elem* priv; } ;
struct nft_set {int dummy; } ;
struct nft_rbtree_elem {int dummy; } ;
struct nft_rbtree {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int __nft_rbtree_insert (struct net const*,struct nft_set const*,struct nft_rbtree_elem*,struct nft_set_ext**) ; 
 struct nft_rbtree* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nft_rbtree_insert(const struct net *net, const struct nft_set *set,
			     const struct nft_set_elem *elem,
			     struct nft_set_ext **ext)
{
	struct nft_rbtree *priv = nft_set_priv(set);
	struct nft_rbtree_elem *rbe = elem->priv;
	int err;

	write_lock_bh(&priv->lock);
	write_seqcount_begin(&priv->count);
	err = __nft_rbtree_insert(net, set, rbe, ext);
	write_seqcount_end(&priv->count);
	write_unlock_bh(&priv->lock);

	return err;
}