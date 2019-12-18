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

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int const COEFF_SIZE ; 

__attribute__((used)) static inline void init_coeff_ram_cache(u8 *cache)
{
	static const u8 norm_addrs[] = { 0x00, 0x05, 0x0a, 0x0f, 0x14, 0x19,
		0x1f, 0x20, 0x25, 0x2a, 0x2f, 0x34, 0x39, 0x3f, 0x40, 0x45,
		0x4a, 0x4f, 0x54, 0x59, 0x5f, 0x60, 0x65, 0x6a, 0x6f, 0x74,
		0x79, 0x7f, 0x80, 0x85, 0x8c, 0x91, 0x96, 0x97, 0x9c, 0xa3,
		0xa8, 0xad, 0xaf, 0xb0, 0xb5, 0xba, 0xbf, 0xc4, 0xc9};
	int i;

	for (i = 0; i < ARRAY_SIZE(norm_addrs); i++)
		cache[((norm_addrs[i] + 1) * COEFF_SIZE) - 1] = 0x40;
}