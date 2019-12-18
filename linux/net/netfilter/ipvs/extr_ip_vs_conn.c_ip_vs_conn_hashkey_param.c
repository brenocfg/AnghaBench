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
struct ip_vs_conn_param {int /*<<< orphan*/  protocol; int /*<<< orphan*/  af; int /*<<< orphan*/  ipvs; int /*<<< orphan*/  vport; union nf_inet_addr* vaddr; int /*<<< orphan*/  cport; union nf_inet_addr* caddr; TYPE_1__* pe; scalar_t__ pe_data; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {unsigned int (* hashkey_raw ) (struct ip_vs_conn_param const*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 unsigned int ip_vs_conn_hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_rnd ; 
 unsigned int ip_vs_conn_tab_mask ; 
 scalar_t__ likely (int) ; 
 unsigned int stub1 (struct ip_vs_conn_param const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int ip_vs_conn_hashkey_param(const struct ip_vs_conn_param *p,
					     bool inverse)
{
	const union nf_inet_addr *addr;
	__be16 port;

	if (p->pe_data && p->pe->hashkey_raw)
		return p->pe->hashkey_raw(p, ip_vs_conn_rnd, inverse) &
			ip_vs_conn_tab_mask;

	if (likely(!inverse)) {
		addr = p->caddr;
		port = p->cport;
	} else {
		addr = p->vaddr;
		port = p->vport;
	}

	return ip_vs_conn_hashkey(p->ipvs, p->af, p->protocol, addr, port);
}