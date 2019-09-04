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
typedef  int /*<<< orphan*/  u32 ;
struct nft_set_ext {int dummy; } ;
struct nft_set {int dummy; } ;
struct nft_rbtree {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int __nft_rbtree_lookup (struct net const*,struct nft_set const*,int /*<<< orphan*/  const*,struct nft_set_ext const**,unsigned int) ; 
 struct nft_rbtree* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 unsigned int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nft_rbtree_lookup(const struct net *net, const struct nft_set *set,
			      const u32 *key, const struct nft_set_ext **ext)
{
	struct nft_rbtree *priv = nft_set_priv(set);
	unsigned int seq = read_seqcount_begin(&priv->count);
	bool ret;

	ret = __nft_rbtree_lookup(net, set, key, ext, seq);
	if (ret || !read_seqcount_retry(&priv->count, seq))
		return ret;

	read_lock_bh(&priv->lock);
	seq = read_seqcount_begin(&priv->count);
	ret = __nft_rbtree_lookup(net, set, key, ext, seq);
	read_unlock_bh(&priv->lock);

	return ret;
}