#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {char const* table; int /*<<< orphan*/  family; int /*<<< orphan*/  hook_mask; int /*<<< orphan*/  targinfo; int /*<<< orphan*/  target; struct ip6t_entry* entryinfo; struct net* net; } ;
struct TYPE_5__ {int /*<<< orphan*/  target; } ;
struct TYPE_6__ {scalar_t__ target_size; TYPE_2__ kernel; } ;
struct xt_entry_target {TYPE_3__ u; int /*<<< orphan*/  data; } ;
struct net {int dummy; } ;
struct TYPE_4__ {int invflags; int /*<<< orphan*/  proto; } ;
struct ip6t_entry {TYPE_1__ ipv6; int /*<<< orphan*/  comefrom; } ;

/* Variables and functions */
 int IP6T_INV_PROTO ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 struct xt_entry_target* ip6t_get_target (struct ip6t_entry*) ; 
 int xt_check_target (struct xt_tgchk_param*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_target(struct ip6t_entry *e, struct net *net, const char *name)
{
	struct xt_entry_target *t = ip6t_get_target(e);
	struct xt_tgchk_param par = {
		.net       = net,
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_IPV6,
	};

	return xt_check_target(&par, t->u.target_size - sizeof(*t),
			       e->ipv6.proto,
			       e->ipv6.invflags & IP6T_INV_PROTO);
}