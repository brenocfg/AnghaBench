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
struct __ip6_tnl_parm {int collect_md; void* fwmark; void* flags; void* flowinfo; void* encap_limit; void* hop_limit; void* raddr; void* laddr; void* o_key; void* i_key; void* o_flags; void* i_flags; void* link; } ;

/* Variables and functions */
 size_t IFLA_GRE_COLLECT_METADATA ; 
 size_t IFLA_GRE_ENCAP_LIMIT ; 
 size_t IFLA_GRE_FLAGS ; 
 size_t IFLA_GRE_FLOWINFO ; 
 size_t IFLA_GRE_FWMARK ; 
 size_t IFLA_GRE_IFLAGS ; 
 size_t IFLA_GRE_IKEY ; 
 size_t IFLA_GRE_LINK ; 
 size_t IFLA_GRE_LOCAL ; 
 size_t IFLA_GRE_OFLAGS ; 
 size_t IFLA_GRE_OKEY ; 
 size_t IFLA_GRE_REMOTE ; 
 size_t IFLA_GRE_TTL ; 
 void* gre_flags_to_tnl_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct __ip6_tnl_parm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 void* nla_get_be32 (struct nlattr*) ; 
 void* nla_get_in6_addr (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static void ip6gre_netlink_parms(struct nlattr *data[],
				struct __ip6_tnl_parm *parms)
{
	memset(parms, 0, sizeof(*parms));

	if (!data)
		return;

	if (data[IFLA_GRE_LINK])
		parms->link = nla_get_u32(data[IFLA_GRE_LINK]);

	if (data[IFLA_GRE_IFLAGS])
		parms->i_flags = gre_flags_to_tnl_flags(
				nla_get_be16(data[IFLA_GRE_IFLAGS]));

	if (data[IFLA_GRE_OFLAGS])
		parms->o_flags = gre_flags_to_tnl_flags(
				nla_get_be16(data[IFLA_GRE_OFLAGS]));

	if (data[IFLA_GRE_IKEY])
		parms->i_key = nla_get_be32(data[IFLA_GRE_IKEY]);

	if (data[IFLA_GRE_OKEY])
		parms->o_key = nla_get_be32(data[IFLA_GRE_OKEY]);

	if (data[IFLA_GRE_LOCAL])
		parms->laddr = nla_get_in6_addr(data[IFLA_GRE_LOCAL]);

	if (data[IFLA_GRE_REMOTE])
		parms->raddr = nla_get_in6_addr(data[IFLA_GRE_REMOTE]);

	if (data[IFLA_GRE_TTL])
		parms->hop_limit = nla_get_u8(data[IFLA_GRE_TTL]);

	if (data[IFLA_GRE_ENCAP_LIMIT])
		parms->encap_limit = nla_get_u8(data[IFLA_GRE_ENCAP_LIMIT]);

	if (data[IFLA_GRE_FLOWINFO])
		parms->flowinfo = nla_get_be32(data[IFLA_GRE_FLOWINFO]);

	if (data[IFLA_GRE_FLAGS])
		parms->flags = nla_get_u32(data[IFLA_GRE_FLAGS]);

	if (data[IFLA_GRE_FWMARK])
		parms->fwmark = nla_get_u32(data[IFLA_GRE_FWMARK]);

	if (data[IFLA_GRE_COLLECT_METADATA])
		parms->collect_md = true;
}