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

/* Variables and functions */
 int BITS_PER_BYTE ; 

__attribute__((used)) static inline u32 nft_bitmap_size(u32 klen)
{
	return ((2 << ((klen * BITS_PER_BYTE) - 1)) / BITS_PER_BYTE) << 1;
}