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
struct tc_skbprio_qopt {int /*<<< orphan*/  limit; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  limit; } ;

/* Variables and functions */
 struct tc_skbprio_qopt* nla_data (struct nlattr*) ; 

__attribute__((used)) static int skbprio_change(struct Qdisc *sch, struct nlattr *opt,
			struct netlink_ext_ack *extack)
{
	struct tc_skbprio_qopt *ctl = nla_data(opt);

	sch->limit = ctl->limit;
	return 0;
}