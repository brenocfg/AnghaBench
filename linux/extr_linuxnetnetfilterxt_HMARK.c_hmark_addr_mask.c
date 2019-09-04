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
typedef  int const __be32 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int const hmark_addr6_mask (int const*,int const*) ; 

__attribute__((used)) static inline __be32
hmark_addr_mask(int l3num, const __be32 *addr32, const __be32 *mask)
{
	switch (l3num) {
	case AF_INET:
		return *addr32 & *mask;
	case AF_INET6:
		return hmark_addr6_mask(addr32, mask);
	}
	return 0;
}