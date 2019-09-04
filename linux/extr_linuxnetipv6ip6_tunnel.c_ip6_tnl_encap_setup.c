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
struct ip_tunnel_encap {int /*<<< orphan*/  flags; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  type; } ;
struct ip6_tnl {int encap_hlen; int hlen; int tun_hlen; TYPE_1__ encap; } ;

/* Variables and functions */
 int ip6_encap_hlen (struct ip_tunnel_encap*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int ip6_tnl_encap_setup(struct ip6_tnl *t,
			struct ip_tunnel_encap *ipencap)
{
	int hlen;

	memset(&t->encap, 0, sizeof(t->encap));

	hlen = ip6_encap_hlen(ipencap);
	if (hlen < 0)
		return hlen;

	t->encap.type = ipencap->type;
	t->encap.sport = ipencap->sport;
	t->encap.dport = ipencap->dport;
	t->encap.flags = ipencap->flags;

	t->encap_hlen = hlen;
	t->hlen = t->encap_hlen + t->tun_hlen;

	return 0;
}