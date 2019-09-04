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
typedef  size_t u32 ;

/* Variables and functions */

__attribute__((used)) static inline bool
nft_bitmap_active(const u8 *bitmap, u32 idx, u32 off, u8 genmask)
{
	return (bitmap[idx] & (0x3 << off)) & (genmask << off);
}