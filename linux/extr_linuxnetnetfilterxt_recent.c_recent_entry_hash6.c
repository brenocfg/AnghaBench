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
union nf_inet_addr {scalar_t__ ip6; } ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  hash_rnd ; 
 int ip_list_hash_size ; 
 int jhash2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int recent_entry_hash6(const union nf_inet_addr *addr)
{
	return jhash2((u32 *)addr->ip6, ARRAY_SIZE(addr->ip6), hash_rnd) &
	       (ip_list_hash_size - 1);
}