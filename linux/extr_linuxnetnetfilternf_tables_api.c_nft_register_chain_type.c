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
struct nft_chain_type {size_t family; size_t type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFNL_SUBSYS_NFTABLES ; 
 size_t NFPROTO_NUMPROTO ; 
 scalar_t__ WARN_ON (int) ; 
 struct nft_chain_type const*** chain_type ; 
 int /*<<< orphan*/  nfnl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_unlock (int /*<<< orphan*/ ) ; 

void nft_register_chain_type(const struct nft_chain_type *ctype)
{
	if (WARN_ON(ctype->family >= NFPROTO_NUMPROTO))
		return;

	nfnl_lock(NFNL_SUBSYS_NFTABLES);
	if (WARN_ON(chain_type[ctype->family][ctype->type] != NULL)) {
		nfnl_unlock(NFNL_SUBSYS_NFTABLES);
		return;
	}
	chain_type[ctype->family][ctype->type] = ctype;
	nfnl_unlock(NFNL_SUBSYS_NFTABLES);
}