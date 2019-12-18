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
typedef  scalar_t__ u32 ;
struct in6_addr {scalar_t__* s6_addr32; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (scalar_t__ const) ; 
 scalar_t__ ntohl (scalar_t__) ; 

int rds_addr_cmp(const struct in6_addr *addr1,
		 const struct in6_addr *addr2)
{
#if defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	const __be64 *a1, *a2;
	u64 x, y;

	a1 = (__be64 *)addr1;
	a2 = (__be64 *)addr2;

	if (*a1 != *a2) {
		if (be64_to_cpu(*a1) < be64_to_cpu(*a2))
			return -1;
		else
			return 1;
	} else {
		x = be64_to_cpu(*++a1);
		y = be64_to_cpu(*++a2);
		if (x < y)
			return -1;
		else if (x > y)
			return 1;
		else
			return 0;
	}
#else
	u32 a, b;
	int i;

	for (i = 0; i < 4; i++) {
		if (addr1->s6_addr32[i] != addr2->s6_addr32[i]) {
			a = ntohl(addr1->s6_addr32[i]);
			b = ntohl(addr2->s6_addr32[i]);
			if (a < b)
				return -1;
			else if (a > b)
				return 1;
		}
	}
	return 0;
#endif
}