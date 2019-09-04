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
typedef  int /*<<< orphan*/  u32 ;
struct nft_set_estimate {int size; int /*<<< orphan*/  space; int /*<<< orphan*/  lookup; } ;
struct nft_set_desc {int size; int klen; } ;
struct nft_hash_elem {int dummy; } ;
struct nft_hash {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_SET_CLASS_O_1 ; 
 int /*<<< orphan*/  NFT_SET_CLASS_O_N ; 
 int nft_hash_buckets (int) ; 

__attribute__((used)) static bool nft_hash_fast_estimate(const struct nft_set_desc *desc, u32 features,
			      struct nft_set_estimate *est)
{
	if (!desc->size)
		return false;

	if (desc->klen != 4)
		return false;

	est->size   = sizeof(struct nft_hash) +
		      nft_hash_buckets(desc->size) * sizeof(struct hlist_head) +
		      desc->size * sizeof(struct nft_hash_elem);
	est->lookup = NFT_SET_CLASS_O_1;
	est->space  = NFT_SET_CLASS_O_N;

	return true;
}