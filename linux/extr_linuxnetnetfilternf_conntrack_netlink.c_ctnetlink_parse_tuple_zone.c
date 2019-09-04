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
struct nlattr {int dummy; } ;
struct nf_conntrack_zone {scalar_t__ id; int /*<<< orphan*/  dir; } ;
typedef  enum ctattr_type { ____Placeholder_ctattr_type } ctattr_type ;

/* Variables and functions */
 int CTA_TUPLE_REPLY ; 
 int EINVAL ; 
 scalar_t__ NF_CT_DEFAULT_ZONE_ID ; 
 int /*<<< orphan*/  NF_CT_ZONE_DIR_ORIG ; 
 int /*<<< orphan*/  NF_CT_ZONE_DIR_REPL ; 
 int ctnetlink_parse_zone (struct nlattr*,struct nf_conntrack_zone*) ; 

__attribute__((used)) static int
ctnetlink_parse_tuple_zone(struct nlattr *attr, enum ctattr_type type,
			   struct nf_conntrack_zone *zone)
{
	int ret;

	if (zone->id != NF_CT_DEFAULT_ZONE_ID)
		return -EINVAL;

	ret = ctnetlink_parse_zone(attr, zone);
	if (ret < 0)
		return ret;

	if (type == CTA_TUPLE_REPLY)
		zone->dir = NF_CT_ZONE_DIR_REPL;
	else
		zone->dir = NF_CT_ZONE_DIR_ORIG;

	return 0;
}