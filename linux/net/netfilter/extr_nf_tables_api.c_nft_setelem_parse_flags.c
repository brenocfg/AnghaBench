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
typedef  int u32 ;
struct nlattr {int dummy; } ;
struct nft_set {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int NFT_SET_ELEM_INTERVAL_END ; 
 int NFT_SET_INTERVAL ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nft_setelem_parse_flags(const struct nft_set *set,
				   const struct nlattr *attr, u32 *flags)
{
	if (attr == NULL)
		return 0;

	*flags = ntohl(nla_get_be32(attr));
	if (*flags & ~NFT_SET_ELEM_INTERVAL_END)
		return -EINVAL;
	if (!(set->flags & NFT_SET_INTERVAL) &&
	    *flags & NFT_SET_ELEM_INTERVAL_END)
		return -EINVAL;

	return 0;
}