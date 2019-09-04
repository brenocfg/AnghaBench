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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nft_bitmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ nft_bitmap_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 nft_bitmap_total_size(u32 klen)
{
	return sizeof(struct nft_bitmap) + nft_bitmap_size(klen);
}