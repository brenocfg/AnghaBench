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
struct ip_vs_sh_state {TYPE_1__* buckets; } ;
struct ip_vs_service {int /*<<< orphan*/  af; } ;
struct ip_vs_dest {int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 unsigned int IP_VS_SH_TAB_SIZE ; 
 unsigned int ip_vs_sh_hashkey (int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  is_unavailable (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct ip_vs_dest* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ip_vs_dest *
ip_vs_sh_get_fallback(struct ip_vs_service *svc, struct ip_vs_sh_state *s,
		      const union nf_inet_addr *addr, __be16 port)
{
	unsigned int offset, roffset;
	unsigned int hash, ihash;
	struct ip_vs_dest *dest;

	/* first try the dest it's supposed to go to */
	ihash = ip_vs_sh_hashkey(svc->af, addr, port, 0);
	dest = rcu_dereference(s->buckets[ihash].dest);
	if (!dest)
		return NULL;
	if (!is_unavailable(dest))
		return dest;

	IP_VS_DBG_BUF(6, "SH: selected unavailable server %s:%d, reselecting",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port));

	/* if the original dest is unavailable, loop around the table
	 * starting from ihash to find a new dest
	 */
	for (offset = 0; offset < IP_VS_SH_TAB_SIZE; offset++) {
		roffset = (offset + ihash) % IP_VS_SH_TAB_SIZE;
		hash = ip_vs_sh_hashkey(svc->af, addr, port, roffset);
		dest = rcu_dereference(s->buckets[hash].dest);
		if (!dest)
			break;
		if (!is_unavailable(dest))
			return dest;
		IP_VS_DBG_BUF(6, "SH: selected unavailable "
			      "server %s:%d (offset %d), reselecting",
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port), roffset);
	}

	return NULL;
}