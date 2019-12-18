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
typedef  int /*<<< orphan*/  u32 ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc_class_ops {unsigned long (* find ) (struct Qdisc*,int /*<<< orphan*/ ) ;} ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int TCM_IFINDEX_MAGIC_BLOCK ; 
 scalar_t__ TC_H_MIN (int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct Qdisc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __tcf_qdisc_cl_find(struct Qdisc *q, u32 parent, unsigned long *cl,
			       int ifindex, struct netlink_ext_ack *extack)
{
	if (ifindex == TCM_IFINDEX_MAGIC_BLOCK)
		return 0;

	/* Do we search for filter, attached to class? */
	if (TC_H_MIN(parent)) {
		const struct Qdisc_class_ops *cops = q->ops->cl_ops;

		*cl = cops->find(q, parent);
		if (*cl == 0) {
			NL_SET_ERR_MSG(extack, "Specified class doesn't exist");
			return -ENOENT;
		}
	}

	return 0;
}