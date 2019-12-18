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
struct nft_set_estimate {void* space; void* lookup; int /*<<< orphan*/  size; } ;
struct nft_set_desc {int klen; } ;

/* Variables and functions */
 void* NFT_SET_CLASS_O_1 ; 
 int /*<<< orphan*/  nft_bitmap_total_size (int) ; 

__attribute__((used)) static bool nft_bitmap_estimate(const struct nft_set_desc *desc, u32 features,
				struct nft_set_estimate *est)
{
	/* Make sure bitmaps we don't get bitmaps larger than 16 Kbytes. */
	if (desc->klen > 2)
		return false;

	est->size   = nft_bitmap_total_size(desc->klen);
	est->lookup = NFT_SET_CLASS_O_1;
	est->space  = NFT_SET_CLASS_O_1;

	return true;
}