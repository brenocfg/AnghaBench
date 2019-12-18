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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 unsigned int __xfrm6_pref_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int __xfrm6_dpref_spref_hash(const xfrm_address_t *daddr,
						    const xfrm_address_t *saddr,
						    __u8 dbits,
						    __u8 sbits)
{
	return __xfrm6_pref_hash(daddr, dbits) ^
	       __xfrm6_pref_hash(saddr, sbits);
}