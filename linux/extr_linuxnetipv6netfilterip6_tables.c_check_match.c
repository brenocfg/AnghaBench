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
struct xt_mtchk_param {int /*<<< orphan*/  matchinfo; int /*<<< orphan*/  match; struct ip6t_ip6* entryinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  match; } ;
struct TYPE_4__ {scalar_t__ match_size; TYPE_1__ kernel; } ;
struct xt_entry_match {TYPE_2__ u; int /*<<< orphan*/  data; } ;
struct ip6t_ip6 {int invflags; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int IP6T_INV_PROTO ; 
 int xt_check_match (struct xt_mtchk_param*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_match(struct xt_entry_match *m, struct xt_mtchk_param *par)
{
	const struct ip6t_ip6 *ipv6 = par->entryinfo;

	par->match     = m->u.kernel.match;
	par->matchinfo = m->data;

	return xt_check_match(par, m->u.match_size - sizeof(*m),
			      ipv6->proto, ipv6->invflags & IP6T_INV_PROTO);
}