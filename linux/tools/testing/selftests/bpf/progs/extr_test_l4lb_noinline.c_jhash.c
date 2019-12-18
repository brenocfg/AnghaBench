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
 int JHASH_INITVAL ; 
 int /*<<< orphan*/  __jhash_final (int,int,int) ; 
 int /*<<< orphan*/  __jhash_mix (int,int,int) ; 

__attribute__((used)) static u32 jhash(const void *key, u32 length, u32 initval)
{
	u32 a, b, c;
	const unsigned char *k = key;

	a = b = c = JHASH_INITVAL + length + initval;

	while (length > 12) {
		a += *(u32 *)(k);
		b += *(u32 *)(k + 4);
		c += *(u32 *)(k + 8);
		__jhash_mix(a, b, c);
		length -= 12;
		k += 12;
	}
	switch (length) {
	case 12: c += (u32)k[11]<<24;
	case 11: c += (u32)k[10]<<16;
	case 10: c += (u32)k[9]<<8;
	case 9:  c += k[8];
	case 8:  b += (u32)k[7]<<24;
	case 7:  b += (u32)k[6]<<16;
	case 6:  b += (u32)k[5]<<8;
	case 5:  b += k[4];
	case 4:  a += (u32)k[3]<<24;
	case 3:  a += (u32)k[2]<<16;
	case 2:  a += (u32)k[1]<<8;
	case 1:  a += k[0];
		 __jhash_final(a, b, c);
	case 0: /* Nothing left to add */
		break;
	}

	return c;
}