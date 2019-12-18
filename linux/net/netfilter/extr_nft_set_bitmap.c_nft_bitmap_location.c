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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nft_set {int klen; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 

__attribute__((used)) static inline void nft_bitmap_location(const struct nft_set *set,
				       const void *key,
				       u32 *idx, u32 *off)
{
	u32 k;

	if (set->klen == 2)
		k = *(u16 *)key;
	else
		k = *(u8 *)key;
	k <<= 1;

	*idx = k / BITS_PER_BYTE;
	*off = k % BITS_PER_BYTE;
}