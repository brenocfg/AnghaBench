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
struct xt_mtchk_param {int /*<<< orphan*/  nft_compat; struct ebt_entry* entryinfo; struct ebt_stp_info* matchinfo; } ;
struct ebt_stp_info {int bitmask; int invflags; } ;
struct ebt_entry {int bitmask; int /*<<< orphan*/  destmsk; int /*<<< orphan*/  destmac; } ;

/* Variables and functions */
 int EBT_DESTMAC ; 
 int EBT_STP_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  eth_stp_addr ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ebt_stp_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_stp_info *info = par->matchinfo;
	const struct ebt_entry *e = par->entryinfo;

	if (info->bitmask & ~EBT_STP_MASK || info->invflags & ~EBT_STP_MASK ||
	    !(info->bitmask & EBT_STP_MASK))
		return -EINVAL;
	/* Make sure the match only receives stp frames */
	if (!par->nft_compat &&
	    (!ether_addr_equal(e->destmac, eth_stp_addr) ||
	     !(e->bitmask & EBT_DESTMAC) ||
	     !is_broadcast_ether_addr(e->destmsk)))
		return -EINVAL;

	return 0;
}