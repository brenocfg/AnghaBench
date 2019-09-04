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
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* egress_block_set ) (struct Qdisc*,scalar_t__) ;int /*<<< orphan*/  (* ingress_block_set ) (struct Qdisc*,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t TCA_EGRESS_BLOCK ; 
 size_t TCA_INGRESS_BLOCK ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct Qdisc*,scalar_t__) ; 

__attribute__((used)) static int qdisc_block_indexes_set(struct Qdisc *sch, struct nlattr **tca,
				   struct netlink_ext_ack *extack)
{
	u32 block_index;

	if (tca[TCA_INGRESS_BLOCK]) {
		block_index = nla_get_u32(tca[TCA_INGRESS_BLOCK]);

		if (!block_index) {
			NL_SET_ERR_MSG(extack, "Ingress block index cannot be 0");
			return -EINVAL;
		}
		if (!sch->ops->ingress_block_set) {
			NL_SET_ERR_MSG(extack, "Ingress block sharing is not supported");
			return -EOPNOTSUPP;
		}
		sch->ops->ingress_block_set(sch, block_index);
	}
	if (tca[TCA_EGRESS_BLOCK]) {
		block_index = nla_get_u32(tca[TCA_EGRESS_BLOCK]);

		if (!block_index) {
			NL_SET_ERR_MSG(extack, "Egress block index cannot be 0");
			return -EINVAL;
		}
		if (!sch->ops->egress_block_set) {
			NL_SET_ERR_MSG(extack, "Egress block sharing is not supported");
			return -EOPNOTSUPP;
		}
		sch->ops->egress_block_set(sch, block_index);
	}
	return 0;
}