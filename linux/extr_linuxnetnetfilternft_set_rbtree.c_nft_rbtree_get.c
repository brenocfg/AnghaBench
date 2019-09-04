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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct nft_set_elem {TYPE_1__ key; } ;
struct nft_set {int dummy; } ;
typedef  void nft_rbtree_elem ;
struct nft_rbtree {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int __nft_rbtree_get (struct net const*,struct nft_set const*,int /*<<< orphan*/  const*,void**,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_genmask_cur (struct net const*) ; 
 struct nft_rbtree* nft_set_priv (struct nft_set const*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 unsigned int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *nft_rbtree_get(const struct net *net, const struct nft_set *set,
			    const struct nft_set_elem *elem, unsigned int flags)
{
	struct nft_rbtree *priv = nft_set_priv(set);
	unsigned int seq = read_seqcount_begin(&priv->count);
	struct nft_rbtree_elem *rbe = ERR_PTR(-ENOENT);
	const u32 *key = (const u32 *)&elem->key.val;
	u8 genmask = nft_genmask_cur(net);
	bool ret;

	ret = __nft_rbtree_get(net, set, key, &rbe, seq, flags, genmask);
	if (ret || !read_seqcount_retry(&priv->count, seq))
		return rbe;

	read_lock_bh(&priv->lock);
	seq = read_seqcount_begin(&priv->count);
	ret = __nft_rbtree_get(net, set, key, &rbe, seq, flags, genmask);
	if (!ret)
		rbe = ERR_PTR(-ENOENT);
	read_unlock_bh(&priv->lock);

	return rbe;
}