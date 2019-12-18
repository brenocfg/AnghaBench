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
struct qdisc_walker {int dummy; } ;
struct qdisc_dump_args {TYPE_2__* cb; int /*<<< orphan*/  skb; } ;
struct Qdisc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_3__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWTCLASS ; 
 int tc_fill_tclass (int /*<<< orphan*/ ,struct Qdisc*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qdisc_class_dump(struct Qdisc *q, unsigned long cl,
			    struct qdisc_walker *arg)
{
	struct qdisc_dump_args *a = (struct qdisc_dump_args *)arg;

	return tc_fill_tclass(a->skb, q, cl, NETLINK_CB(a->cb->skb).portid,
			      a->cb->nlh->nlmsg_seq, NLM_F_MULTI,
			      RTM_NEWTCLASS);
}