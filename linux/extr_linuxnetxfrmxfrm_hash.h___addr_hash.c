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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int __xfrm4_dpref_spref_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int __xfrm6_dpref_spref_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int __addr_hash(const xfrm_address_t *daddr,
				       const xfrm_address_t *saddr,
				       unsigned short family,
				       unsigned int hmask,
				       u8 dbits, u8 sbits)
{
	unsigned int h = 0;

	switch (family) {
	case AF_INET:
		h = __xfrm4_dpref_spref_hash(daddr, saddr, dbits, sbits);
		break;

	case AF_INET6:
		h = __xfrm6_dpref_spref_hash(daddr, saddr, dbits, sbits);
		break;
	}
	h ^= (h >> 16);
	return h & hmask;
}