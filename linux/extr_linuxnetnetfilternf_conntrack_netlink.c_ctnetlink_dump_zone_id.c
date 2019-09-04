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
struct sk_buff {int dummy; } ;
struct nf_conntrack_zone {scalar_t__ id; int dir; } ;

/* Variables and functions */
 scalar_t__ NF_CT_DEFAULT_ZONE_ID ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctnetlink_dump_zone_id(struct sk_buff *skb, int attrtype,
				  const struct nf_conntrack_zone *zone, int dir)
{
	if (zone->id == NF_CT_DEFAULT_ZONE_ID || zone->dir != dir)
		return 0;
	if (nla_put_be16(skb, attrtype, htons(zone->id)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -1;
}