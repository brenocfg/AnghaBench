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
struct TYPE_4__ {int /*<<< orphan*/  a4; } ;
typedef  TYPE_1__ xfrm_address_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int __bits2mask32 (int /*<<< orphan*/ ) ; 
 unsigned int jhash_2words (int,int,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int __xfrm4_dpref_spref_hash(const xfrm_address_t *daddr,
						    const xfrm_address_t *saddr,
						    __u8 dbits,
						    __u8 sbits)
{
	return jhash_2words(ntohl(daddr->a4) & __bits2mask32(dbits),
			    ntohl(saddr->a4) & __bits2mask32(sbits),
			    0);
}