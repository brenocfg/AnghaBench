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
struct nft_set_elem {struct nft_rbtree_elem* priv; } ;
struct nft_set {int dummy; } ;
struct nft_rbtree_elem {int /*<<< orphan*/  node; } ;
struct nft_rbtree {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; int /*<<< orphan*/  root; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct nft_rbtree* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nft_rbtree_remove(const struct net *net,
			      const struct nft_set *set,
			      const struct nft_set_elem *elem)
{
	struct nft_rbtree *priv = nft_set_priv(set);
	struct nft_rbtree_elem *rbe = elem->priv;

	write_lock_bh(&priv->lock);
	write_seqcount_begin(&priv->count);
	rb_erase(&rbe->node, &priv->root);
	write_seqcount_end(&priv->count);
	write_unlock_bh(&priv->lock);
}