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
struct TYPE_2__ {int msg_id; } ;
union bfi_cee_i2h_msg_u {TYPE_1__ mh; } ;
struct bfi_mbmsg_s {int dummy; } ;
struct bfi_cee_get_rsp_s {int cmd_status; } ;
struct bfa_cee_s {int dummy; } ;

/* Variables and functions */
#define  BFI_CEE_I2H_GET_CFG_RSP 130 
#define  BFI_CEE_I2H_GET_STATS_RSP 129 
#define  BFI_CEE_I2H_RESET_STATS_RSP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_cee_get_attr_isr (struct bfa_cee_s*,int) ; 
 int /*<<< orphan*/  bfa_cee_get_stats_isr (struct bfa_cee_s*,int) ; 
 int /*<<< orphan*/  bfa_cee_reset_stats_isr (struct bfa_cee_s*,int) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_cee_s*,int) ; 

void
bfa_cee_isr(void *cbarg, struct bfi_mbmsg_s *m)
{
	union bfi_cee_i2h_msg_u *msg;
	struct bfi_cee_get_rsp_s *get_rsp;
	struct bfa_cee_s *cee = (struct bfa_cee_s *) cbarg;
	msg = (union bfi_cee_i2h_msg_u *) m;
	get_rsp = (struct bfi_cee_get_rsp_s *) m;
	bfa_trc(cee, msg->mh.msg_id);
	switch (msg->mh.msg_id) {
	case BFI_CEE_I2H_GET_CFG_RSP:
		bfa_trc(cee, get_rsp->cmd_status);
		bfa_cee_get_attr_isr(cee, get_rsp->cmd_status);
		break;
	case BFI_CEE_I2H_GET_STATS_RSP:
		bfa_cee_get_stats_isr(cee, get_rsp->cmd_status);
		break;
	case BFI_CEE_I2H_RESET_STATS_RSP:
		bfa_cee_reset_stats_isr(cee, get_rsp->cmd_status);
		break;
	default:
		WARN_ON(1);
	}
}