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
typedef  int u64 ;
struct nlattr {int dummy; } ;
struct nft_set_desc {int /*<<< orphan*/  size; } ;
struct nft_hash {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int nft_hash_buckets (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 nft_hash_privsize(const struct nlattr * const nla[],
			     const struct nft_set_desc *desc)
{
	return sizeof(struct nft_hash) +
	       nft_hash_buckets(desc->size) * sizeof(struct hlist_head);
}