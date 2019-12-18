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
struct nf_conntrack_zone {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_DIR ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_ID ; 
 int /*<<< orphan*/  nf_ct_zone_init (struct nf_conntrack_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctnetlink_parse_zone(const struct nlattr *attr,
		     struct nf_conntrack_zone *zone)
{
	nf_ct_zone_init(zone, NF_CT_DEFAULT_ZONE_ID,
			NF_CT_DEFAULT_ZONE_DIR, 0);
#ifdef CONFIG_NF_CONNTRACK_ZONES
	if (attr)
		zone->id = ntohs(nla_get_be16(attr));
#else
	if (attr)
		return -EOPNOTSUPP;
#endif
	return 0;
}