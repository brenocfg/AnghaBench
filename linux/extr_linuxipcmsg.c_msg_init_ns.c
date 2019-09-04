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
struct ipc_namespace {int /*<<< orphan*/ * ids; int /*<<< orphan*/  msg_hdrs; int /*<<< orphan*/  msg_bytes; int /*<<< orphan*/  msg_ctlmni; int /*<<< orphan*/  msg_ctlmnb; int /*<<< orphan*/  msg_ctlmax; } ;

/* Variables and functions */
 size_t IPC_MSG_IDS ; 
 int /*<<< orphan*/  MSGMAX ; 
 int /*<<< orphan*/  MSGMNB ; 
 int /*<<< orphan*/  MSGMNI ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_init_ids (int /*<<< orphan*/ *) ; 

void msg_init_ns(struct ipc_namespace *ns)
{
	ns->msg_ctlmax = MSGMAX;
	ns->msg_ctlmnb = MSGMNB;
	ns->msg_ctlmni = MSGMNI;

	atomic_set(&ns->msg_bytes, 0);
	atomic_set(&ns->msg_hdrs, 0);
	ipc_init_ids(&ns->ids[IPC_MSG_IDS]);
}