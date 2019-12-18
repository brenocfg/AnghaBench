#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct ip_vs_dh_state {TYPE_1__* buckets; } ;
struct ip_vs_dest {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 size_t ip_vs_dh_hashkey (int,union nf_inet_addr const*) ; 
 struct ip_vs_dest* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ip_vs_dest *
ip_vs_dh_get(int af, struct ip_vs_dh_state *s, const union nf_inet_addr *addr)
{
	return rcu_dereference(s->buckets[ip_vs_dh_hashkey(af, addr)].dest);
}