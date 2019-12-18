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
struct xt_mtchk_param {struct ebt_entry* entryinfo; struct ebt_arp_info* matchinfo; } ;
struct ebt_entry {scalar_t__ ethproto; int invflags; } ;
struct ebt_arp_info {int bitmask; int invflags; } ;

/* Variables and functions */
 int EBT_ARP_MASK ; 
 int EBT_IPROTO ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_RARP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ebt_arp_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_arp_info *info = par->matchinfo;
	const struct ebt_entry *e = par->entryinfo;

	if ((e->ethproto != htons(ETH_P_ARP) &&
	   e->ethproto != htons(ETH_P_RARP)) ||
	   e->invflags & EBT_IPROTO)
		return -EINVAL;
	if (info->bitmask & ~EBT_ARP_MASK || info->invflags & ~EBT_ARP_MASK)
		return -EINVAL;
	return 0;
}