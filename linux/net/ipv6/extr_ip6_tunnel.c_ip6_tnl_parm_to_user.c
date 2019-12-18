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
struct ip6_tnl_parm {int /*<<< orphan*/  name; int /*<<< orphan*/  proto; int /*<<< orphan*/  link; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;
struct __ip6_tnl_parm {int /*<<< orphan*/  name; int /*<<< orphan*/  proto; int /*<<< orphan*/  link; int /*<<< orphan*/  flowinfo; int /*<<< orphan*/  encap_limit; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flags; int /*<<< orphan*/  raddr; int /*<<< orphan*/  laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ip6_tnl_parm_to_user(struct ip6_tnl_parm *u, const struct __ip6_tnl_parm *p)
{
	u->laddr = p->laddr;
	u->raddr = p->raddr;
	u->flags = p->flags;
	u->hop_limit = p->hop_limit;
	u->encap_limit = p->encap_limit;
	u->flowinfo = p->flowinfo;
	u->link = p->link;
	u->proto = p->proto;
	memcpy(u->name, p->name, sizeof(u->name));
}