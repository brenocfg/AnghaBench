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
struct nft_expr {int dummy; } ;
struct nft_connlimit {int /*<<< orphan*/  list; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int nf_conncount_gc_list (struct net*,int /*<<< orphan*/ *) ; 
 struct nft_connlimit* nft_expr_priv (struct nft_expr const*) ; 

__attribute__((used)) static bool nft_connlimit_gc(struct net *net, const struct nft_expr *expr)
{
	struct nft_connlimit *priv = nft_expr_priv(expr);
	bool ret;

	local_bh_disable();
	ret = nf_conncount_gc_list(net, &priv->list);
	local_bh_enable();

	return ret;
}