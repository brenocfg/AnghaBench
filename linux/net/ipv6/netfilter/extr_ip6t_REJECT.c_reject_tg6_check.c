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
struct xt_tgchk_param {struct ip6t_entry* entryinfo; struct ip6t_reject_info* targinfo; } ;
struct ip6t_reject_info {scalar_t__ with; } ;
struct TYPE_2__ {int flags; scalar_t__ proto; int invflags; } ;
struct ip6t_entry {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int EINVAL ; 
 int IP6T_F_PROTO ; 
 scalar_t__ IP6T_ICMP6_ECHOREPLY ; 
 scalar_t__ IP6T_TCP_RESET ; 
 scalar_t__ IPPROTO_TCP ; 
 int XT_INV_PROTO ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*) ; 

__attribute__((used)) static int reject_tg6_check(const struct xt_tgchk_param *par)
{
	const struct ip6t_reject_info *rejinfo = par->targinfo;
	const struct ip6t_entry *e = par->entryinfo;

	if (rejinfo->with == IP6T_ICMP6_ECHOREPLY) {
		pr_info_ratelimited("ECHOREPLY is not supported\n");
		return -EINVAL;
	} else if (rejinfo->with == IP6T_TCP_RESET) {
		/* Must specify that it's a TCP packet */
		if (!(e->ipv6.flags & IP6T_F_PROTO) ||
		    e->ipv6.proto != IPPROTO_TCP ||
		    (e->ipv6.invflags & XT_INV_PROTO)) {
			pr_info_ratelimited("TCP_RESET illegal for non-tcp\n");
			return -EINVAL;
		}
	}
	return 0;
}