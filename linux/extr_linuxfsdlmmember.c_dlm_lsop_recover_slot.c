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
typedef  scalar_t__ uint32_t ;
struct dlm_slot {int /*<<< orphan*/  slot; int /*<<< orphan*/  nodeid; } ;
struct dlm_member {scalar_t__ comm_seq; int /*<<< orphan*/  slot; int /*<<< orphan*/  nodeid; } ;
struct dlm_ls {int /*<<< orphan*/  ls_ops_arg; TYPE_1__* ls_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recover_slot ) (int /*<<< orphan*/ ,struct dlm_slot*) ;} ;

/* Variables and functions */
 int dlm_comm_seq (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dlm_slot*) ; 

__attribute__((used)) static void dlm_lsop_recover_slot(struct dlm_ls *ls, struct dlm_member *memb)
{
	struct dlm_slot slot;
	uint32_t seq;
	int error;

	if (!ls->ls_ops || !ls->ls_ops->recover_slot)
		return;

	/* if there is no comms connection with this node
	   or the present comms connection is newer
	   than the one when this member was added, then
	   we consider the node to have failed (versus
	   being removed due to dlm_release_lockspace) */

	error = dlm_comm_seq(memb->nodeid, &seq);

	if (!error && seq == memb->comm_seq)
		return;

	slot.nodeid = memb->nodeid;
	slot.slot = memb->slot;

	ls->ls_ops->recover_slot(ls->ls_ops_arg, &slot);
}