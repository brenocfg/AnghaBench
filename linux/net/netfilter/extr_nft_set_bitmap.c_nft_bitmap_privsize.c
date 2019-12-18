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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct nft_set_desc {int dummy; } ;

/* Variables and functions */
 size_t NFTA_SET_KEY_LEN ; 
 int /*<<< orphan*/  nft_bitmap_total_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 nft_bitmap_privsize(const struct nlattr * const nla[],
			       const struct nft_set_desc *desc)
{
	u32 klen = ntohl(nla_get_be32(nla[NFTA_SET_KEY_LEN]));

	return nft_bitmap_total_size(klen);
}