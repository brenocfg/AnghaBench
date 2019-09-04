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
struct tcf_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {struct Qdisc* qdisc; } ;
struct net {int dummy; } ;
struct Qdisc_class_ops {unsigned long (* find ) (struct Qdisc*,int /*<<< orphan*/ ) ;struct tcf_block* (* tcf_block ) (struct Qdisc*,unsigned long,struct netlink_ext_ack*) ;} ;
struct Qdisc {TYPE_1__* ops; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct tcf_block* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int TCM_IFINDEX_MAGIC_BLOCK ; 
 int /*<<< orphan*/  TC_H_MAJ (int /*<<< orphan*/ ) ; 
 scalar_t__ TC_H_MIN (int /*<<< orphan*/ ) ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct Qdisc* qdisc_lookup (struct net_device*,int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct Qdisc*,int /*<<< orphan*/ ) ; 
 struct tcf_block* stub2 (struct Qdisc*,unsigned long,struct netlink_ext_ack*) ; 
 struct tcf_block* tcf_block_lookup (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_block_shared (struct tcf_block*) ; 

__attribute__((used)) static struct tcf_block *tcf_block_find(struct net *net, struct Qdisc **q,
					u32 *parent, unsigned long *cl,
					int ifindex, u32 block_index,
					struct netlink_ext_ack *extack)
{
	struct tcf_block *block;

	if (ifindex == TCM_IFINDEX_MAGIC_BLOCK) {
		block = tcf_block_lookup(net, block_index);
		if (!block) {
			NL_SET_ERR_MSG(extack, "Block of given index was not found");
			return ERR_PTR(-EINVAL);
		}
	} else {
		const struct Qdisc_class_ops *cops;
		struct net_device *dev;

		/* Find link */
		dev = __dev_get_by_index(net, ifindex);
		if (!dev)
			return ERR_PTR(-ENODEV);

		/* Find qdisc */
		if (!*parent) {
			*q = dev->qdisc;
			*parent = (*q)->handle;
		} else {
			*q = qdisc_lookup(dev, TC_H_MAJ(*parent));
			if (!*q) {
				NL_SET_ERR_MSG(extack, "Parent Qdisc doesn't exists");
				return ERR_PTR(-EINVAL);
			}
		}

		/* Is it classful? */
		cops = (*q)->ops->cl_ops;
		if (!cops) {
			NL_SET_ERR_MSG(extack, "Qdisc not classful");
			return ERR_PTR(-EINVAL);
		}

		if (!cops->tcf_block) {
			NL_SET_ERR_MSG(extack, "Class doesn't support blocks");
			return ERR_PTR(-EOPNOTSUPP);
		}

		/* Do we search for filter, attached to class? */
		if (TC_H_MIN(*parent)) {
			*cl = cops->find(*q, *parent);
			if (*cl == 0) {
				NL_SET_ERR_MSG(extack, "Specified class doesn't exist");
				return ERR_PTR(-ENOENT);
			}
		}

		/* And the last stroke */
		block = cops->tcf_block(*q, *cl, extack);
		if (!block)
			return ERR_PTR(-EINVAL);
		if (tcf_block_shared(block)) {
			NL_SET_ERR_MSG(extack, "This filter block is shared. Please use the block index to manipulate the filters");
			return ERR_PTR(-EOPNOTSUPP);
		}
	}

	return block;
}