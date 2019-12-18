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
typedef  int __u8 ;

/* Variables and functions */

__attribute__((used)) static inline u32 __bits2mask32(__u8 bits)
{
	u32 mask32 = 0xffffffff;

	if (bits == 0)
		mask32 = 0;
	else if (bits < 32)
		mask32 <<= (32 - bits);

	return mask32;
}