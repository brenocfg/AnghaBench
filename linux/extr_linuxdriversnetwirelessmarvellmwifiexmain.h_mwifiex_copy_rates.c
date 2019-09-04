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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;

/* Variables and functions */
 size_t MWIFIEX_SUPPORTED_RATES ; 

__attribute__((used)) static inline u32
mwifiex_copy_rates(u8 *dest, u32 pos, u8 *src, int len)
{
	int i;

	for (i = 0; i < len && src[i]; i++, pos++) {
		if (pos >= MWIFIEX_SUPPORTED_RATES)
			break;
		dest[pos] = src[i];
	}

	return pos;
}