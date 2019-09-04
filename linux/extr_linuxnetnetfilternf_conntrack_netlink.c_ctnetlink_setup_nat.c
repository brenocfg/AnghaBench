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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 size_t CTA_NAT_DST ; 
 size_t CTA_NAT_SRC ; 
 int EOPNOTSUPP ; 

__attribute__((used)) static int
ctnetlink_setup_nat(struct nf_conn *ct, const struct nlattr * const cda[])
{
#ifdef CONFIG_NF_NAT_NEEDED
	int ret;

	if (!cda[CTA_NAT_DST] && !cda[CTA_NAT_SRC])
		return 0;

	ret = ctnetlink_parse_nat_setup(ct, NF_NAT_MANIP_DST,
					cda[CTA_NAT_DST]);
	if (ret < 0)
		return ret;

	return ctnetlink_parse_nat_setup(ct, NF_NAT_MANIP_SRC,
					 cda[CTA_NAT_SRC]);
#else
	if (!cda[CTA_NAT_DST] && !cda[CTA_NAT_SRC])
		return 0;
	return -EOPNOTSUPP;
#endif
}