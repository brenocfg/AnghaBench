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
struct tc_fifo_qopt {unsigned int limit; } ;
struct nlattr {int /*<<< orphan*/  nla_len; int /*<<< orphan*/  nla_type; } ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* change ) (struct Qdisc*,struct nlattr*,int /*<<< orphan*/ *) ;scalar_t__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTM_NEWQDISC ; 
 int /*<<< orphan*/  kfree (struct nlattr*) ; 
 struct nlattr* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_attr_size (int) ; 
 scalar_t__ nla_data (struct nlattr*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int stub1 (struct Qdisc*,struct nlattr*,int /*<<< orphan*/ *) ; 

int fifo_set_limit(struct Qdisc *q, unsigned int limit)
{
	struct nlattr *nla;
	int ret = -ENOMEM;

	/* Hack to avoid sending change message to non-FIFO */
	if (strncmp(q->ops->id + 1, "fifo", 4) != 0)
		return 0;

	nla = kmalloc(nla_attr_size(sizeof(struct tc_fifo_qopt)), GFP_KERNEL);
	if (nla) {
		nla->nla_type = RTM_NEWQDISC;
		nla->nla_len = nla_attr_size(sizeof(struct tc_fifo_qopt));
		((struct tc_fifo_qopt *)nla_data(nla))->limit = limit;

		ret = q->ops->change(q, nla, NULL);
		kfree(nla);
	}
	return ret;
}