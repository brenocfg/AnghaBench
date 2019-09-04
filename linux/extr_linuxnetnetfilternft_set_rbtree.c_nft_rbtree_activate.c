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
struct nft_rbtree_elem {int /*<<< orphan*/  ext; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nft_set_elem_change_active (struct net const*,struct nft_set const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nft_set_elem_clear_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nft_rbtree_activate(const struct net *net,
				const struct nft_set *set,
				const struct nft_set_elem *elem)
{
	struct nft_rbtree_elem *rbe = elem->priv;

	nft_set_elem_change_active(net, set, &rbe->ext);
	nft_set_elem_clear_busy(&rbe->ext);
}