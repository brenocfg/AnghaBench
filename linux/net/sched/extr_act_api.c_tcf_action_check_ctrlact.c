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
typedef  int u32 ;
struct tcf_proto {TYPE_1__* chain; } ;
struct tcf_chain {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ TC_ACT_EXT_CMP (int,int /*<<< orphan*/ ) ; 
 int TC_ACT_EXT_OPCODE (int) ; 
 int TC_ACT_EXT_OPCODE_MAX ; 
 int TC_ACT_EXT_VAL_MASK ; 
 int /*<<< orphan*/  TC_ACT_GOTO_CHAIN ; 
 int TC_ACT_UNSPEC ; 
 int TC_ACT_VALUE_MAX ; 
 struct tcf_chain* tcf_chain_get_by_act (int /*<<< orphan*/ ,int) ; 

int tcf_action_check_ctrlact(int action, struct tcf_proto *tp,
			     struct tcf_chain **newchain,
			     struct netlink_ext_ack *extack)
{
	int opcode = TC_ACT_EXT_OPCODE(action), ret = -EINVAL;
	u32 chain_index;

	if (!opcode)
		ret = action > TC_ACT_VALUE_MAX ? -EINVAL : 0;
	else if (opcode <= TC_ACT_EXT_OPCODE_MAX || action == TC_ACT_UNSPEC)
		ret = 0;
	if (ret) {
		NL_SET_ERR_MSG(extack, "invalid control action");
		goto end;
	}

	if (TC_ACT_EXT_CMP(action, TC_ACT_GOTO_CHAIN)) {
		chain_index = action & TC_ACT_EXT_VAL_MASK;
		if (!tp || !newchain) {
			ret = -EINVAL;
			NL_SET_ERR_MSG(extack,
				       "can't goto NULL proto/chain");
			goto end;
		}
		*newchain = tcf_chain_get_by_act(tp->chain->block, chain_index);
		if (!*newchain) {
			ret = -ENOMEM;
			NL_SET_ERR_MSG(extack,
				       "can't allocate goto_chain");
		}
	}
end:
	return ret;
}