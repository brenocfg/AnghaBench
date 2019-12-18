#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * a6; int /*<<< orphan*/  a4; } ;
typedef  TYPE_1__ xfrm_address_t ;
typedef  int u8 ;
typedef  unsigned long u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned long ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_policy_addr_delta(const xfrm_address_t *a,
				  const xfrm_address_t *b,
				  u8 prefixlen, u16 family)
{
	unsigned int pdw, pbi;
	int delta = 0;

	switch (family) {
	case AF_INET:
		if (sizeof(long) == 4 && prefixlen == 0)
			return ntohl(a->a4) - ntohl(b->a4);
		return (ntohl(a->a4) & ((~0UL << (32 - prefixlen)))) -
		       (ntohl(b->a4) & ((~0UL << (32 - prefixlen))));
	case AF_INET6:
		pdw = prefixlen >> 5;
		pbi = prefixlen & 0x1f;

		if (pdw) {
			delta = memcmp(a->a6, b->a6, pdw << 2);
			if (delta)
				return delta;
		}
		if (pbi) {
			u32 mask = ~0u << (32 - pbi);

			delta = (ntohl(a->a6[pdw]) & mask) -
				(ntohl(b->a6[pdw]) & mask);
		}
		break;
	default:
		break;
	}

	return delta;
}