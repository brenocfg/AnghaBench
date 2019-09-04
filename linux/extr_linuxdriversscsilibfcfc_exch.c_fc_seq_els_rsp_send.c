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
struct fc_seq_els_data {int /*<<< orphan*/  explan; int /*<<< orphan*/  reason; } ;
struct fc_frame {int dummy; } ;
typedef  enum fc_els_cmd { ____Placeholder_fc_els_cmd } fc_els_cmd ;

/* Variables and functions */
#define  ELS_LS_ACC 131 
#define  ELS_LS_RJT 130 
#define  ELS_REC 129 
#define  ELS_RRQ 128 
 int /*<<< orphan*/  FC_LPORT_DBG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fc_exch_els_rec (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_exch_els_rrq (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_seq_ls_acc (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_seq_ls_rjt (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fr_dev (struct fc_frame*) ; 

void fc_seq_els_rsp_send(struct fc_frame *fp, enum fc_els_cmd els_cmd,
			 struct fc_seq_els_data *els_data)
{
	switch (els_cmd) {
	case ELS_LS_RJT:
		fc_seq_ls_rjt(fp, els_data->reason, els_data->explan);
		break;
	case ELS_LS_ACC:
		fc_seq_ls_acc(fp);
		break;
	case ELS_RRQ:
		fc_exch_els_rrq(fp);
		break;
	case ELS_REC:
		fc_exch_els_rec(fp);
		break;
	default:
		FC_LPORT_DBG(fr_dev(fp), "Invalid ELS CMD:%x\n", els_cmd);
	}
}