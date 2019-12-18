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
struct sk_buff {int /*<<< orphan*/  truesize; scalar_t__ data; } ;
struct mpoa_client {int /*<<< orphan*/  parameters; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  params; } ;
struct k_message {int type; TYPE_2__ content; } ;
struct atm_vcc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
#define  CACHE_IMPOS_RCVD 138 
#define  CLEAN_UP_AND_EXIT 137 
 int const DIE ; 
#define  EGRESS_PURGE_RCVD 136 
#define  INGRESS_PURGE_RCVD 135 
#define  MPOA_RES_REPLY_RCVD 134 
#define  MPOA_TRIGGER_RCVD 133 
 int /*<<< orphan*/  MPOA_cache_impos_rcvd (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  MPOA_res_reply_rcvd (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  MPOA_trigger_rcvd (struct k_message*,struct mpoa_client*) ; 
#define  MPS_DEATH 132 
#define  RELOAD 131 
#define  SET_MPC_CTRL_ADDR 130 
#define  SET_MPC_PARAMS 129 
#define  SET_MPS_MAC_ADDR 128 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_up (struct k_message*,struct mpoa_client*,int const) ; 
 int /*<<< orphan*/  dprintk (char*,char*) ; 
 int /*<<< orphan*/  dprintk_cont (char*,...) ; 
 int /*<<< orphan*/  egress_purge_rcvd (struct k_message*,struct mpoa_client*) ; 
 struct mpoa_client* find_mpc_by_vcc (struct atm_vcc*) ; 
 int /*<<< orphan*/  ingress_purge_rcvd (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mps_death (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  refcount_sub_and_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mpc_ctrl_addr_rcvd (struct k_message*,struct mpoa_client*) ; 
 int /*<<< orphan*/  set_mps_mac_addr_rcvd (struct k_message*,struct mpoa_client*) ; 
 TYPE_3__* sk_atm (struct atm_vcc*) ; 

__attribute__((used)) static int msg_from_mpoad(struct atm_vcc *vcc, struct sk_buff *skb)
{

	struct mpoa_client *mpc = find_mpc_by_vcc(vcc);
	struct k_message *mesg = (struct k_message *)skb->data;
	WARN_ON(refcount_sub_and_test(skb->truesize, &sk_atm(vcc)->sk_wmem_alloc));

	if (mpc == NULL) {
		pr_info("no mpc found\n");
		return 0;
	}
	dprintk("(%s)", mpc->dev ? mpc->dev->name : "<unknown>");
	switch (mesg->type) {
	case MPOA_RES_REPLY_RCVD:
		dprintk_cont("mpoa_res_reply_rcvd\n");
		MPOA_res_reply_rcvd(mesg, mpc);
		break;
	case MPOA_TRIGGER_RCVD:
		dprintk_cont("mpoa_trigger_rcvd\n");
		MPOA_trigger_rcvd(mesg, mpc);
		break;
	case INGRESS_PURGE_RCVD:
		dprintk_cont("nhrp_purge_rcvd\n");
		ingress_purge_rcvd(mesg, mpc);
		break;
	case EGRESS_PURGE_RCVD:
		dprintk_cont("egress_purge_reply_rcvd\n");
		egress_purge_rcvd(mesg, mpc);
		break;
	case MPS_DEATH:
		dprintk_cont("mps_death\n");
		mps_death(mesg, mpc);
		break;
	case CACHE_IMPOS_RCVD:
		dprintk_cont("cache_impos_rcvd\n");
		MPOA_cache_impos_rcvd(mesg, mpc);
		break;
	case SET_MPC_CTRL_ADDR:
		dprintk_cont("set_mpc_ctrl_addr\n");
		set_mpc_ctrl_addr_rcvd(mesg, mpc);
		break;
	case SET_MPS_MAC_ADDR:
		dprintk_cont("set_mps_mac_addr\n");
		set_mps_mac_addr_rcvd(mesg, mpc);
		break;
	case CLEAN_UP_AND_EXIT:
		dprintk_cont("clean_up_and_exit\n");
		clean_up(mesg, mpc, DIE);
		break;
	case RELOAD:
		dprintk_cont("reload\n");
		clean_up(mesg, mpc, RELOAD);
		break;
	case SET_MPC_PARAMS:
		dprintk_cont("set_mpc_params\n");
		mpc->parameters = mesg->content.params;
		break;
	default:
		dprintk_cont("unknown message %d\n", mesg->type);
		break;
	}
	kfree_skb(skb);

	return 0;
}