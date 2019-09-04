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
struct ibmvfc_target {int action; int /*<<< orphan*/  add_rport; } ;
typedef  enum ibmvfc_target_action { ____Placeholder_ibmvfc_target_action } ibmvfc_target_action ;

/* Variables and functions */
#define  IBMVFC_TGT_ACTION_DELETED_RPORT 129 
#define  IBMVFC_TGT_ACTION_DEL_RPORT 128 

__attribute__((used)) static void ibmvfc_set_tgt_action(struct ibmvfc_target *tgt,
				  enum ibmvfc_target_action action)
{
	switch (tgt->action) {
	case IBMVFC_TGT_ACTION_DEL_RPORT:
		if (action == IBMVFC_TGT_ACTION_DELETED_RPORT)
			tgt->action = action;
	case IBMVFC_TGT_ACTION_DELETED_RPORT:
		break;
	default:
		if (action == IBMVFC_TGT_ACTION_DEL_RPORT)
			tgt->add_rport = 0;
		tgt->action = action;
		break;
	}
}