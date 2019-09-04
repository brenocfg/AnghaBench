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
typedef  unsigned long u16 ;

/* Variables and functions */
 int IFNAMSIZ ; 

__attribute__((used)) static unsigned long ifname_compare(const char *_a, const char *_b, const char *_mask)
{
#ifdef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	unsigned long ret = ifname_compare_aligned(_a, _b, _mask);
#else
	unsigned long ret = 0;
	const u16 *a = (const u16 *)_a;
	const u16 *b = (const u16 *)_b;
	const u16 *mask = (const u16 *)_mask;
	int i;

	for (i = 0; i < IFNAMSIZ/sizeof(u16); i++)
		ret |= (a[i] ^ b[i]) & mask[i];
#endif
	return ret;
}