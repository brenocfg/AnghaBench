#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct xt_tgchk_param {scalar_t__ family; struct ipt_entry* entryinfo; } ;
struct TYPE_4__ {int invflags; int /*<<< orphan*/  proto; } ;
struct TYPE_3__ {int invflags; int /*<<< orphan*/  proto; } ;
struct ipt_entry {TYPE_2__ ipv6; TYPE_1__ ip; } ;
struct ip6t_entry {TYPE_2__ ipv6; TYPE_1__ ip; } ;

/* Variables and functions */
 int IP6T_INV_PROTO ; 
 int IPT_INV_PROTO ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 

__attribute__((used)) static u8 xt_ct_find_proto(const struct xt_tgchk_param *par)
{
	if (par->family == NFPROTO_IPV4) {
		const struct ipt_entry *e = par->entryinfo;

		if (e->ip.invflags & IPT_INV_PROTO)
			return 0;
		return e->ip.proto;
	} else if (par->family == NFPROTO_IPV6) {
		const struct ip6t_entry *e = par->entryinfo;

		if (e->ipv6.invflags & IP6T_INV_PROTO)
			return 0;
		return e->ipv6.proto;
	} else
		return 0;
}