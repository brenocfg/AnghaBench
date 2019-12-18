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
struct TYPE_2__ {int /*<<< orphan*/  fwmark; int /*<<< orphan*/  proto; int /*<<< orphan*/  link; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;
struct ip6_tnl {int /*<<< orphan*/  dst_cache; TYPE_1__ parms; } ;
struct __ip6_tnl_parm {int /*<<< orphan*/  fwmark; int /*<<< orphan*/  proto; int /*<<< orphan*/  link; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_cache_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_tnl_link_config (struct ip6_tnl*) ; 

__attribute__((used)) static int
ip6_tnl_change(struct ip6_tnl *t, const struct __ip6_tnl_parm *p)
{
	t->parms.laddr = p->laddr;
	t->parms.raddr = p->raddr;
	t->parms.flags = p->flags;
	t->parms.hop_limit = p->hop_limit;
	t->parms.encap_limit = p->encap_limit;
	t->parms.flowinfo = p->flowinfo;
	t->parms.link = p->link;
	t->parms.proto = p->proto;
	t->parms.fwmark = p->fwmark;
	dst_cache_reset(&t->dst_cache);
	ip6_tnl_link_config(t);
	return 0;
}