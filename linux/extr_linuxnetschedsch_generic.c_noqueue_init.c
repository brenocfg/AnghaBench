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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/ * enqueue; } ;

/* Variables and functions */

__attribute__((used)) static int noqueue_init(struct Qdisc *qdisc, struct nlattr *opt,
			struct netlink_ext_ack *extack)
{
	/* register_qdisc() assigns a default of noop_enqueue if unset,
	 * but __dev_queue_xmit() treats noqueue only as such
	 * if this is NULL - so clear it here. */
	qdisc->enqueue = NULL;
	return 0;
}