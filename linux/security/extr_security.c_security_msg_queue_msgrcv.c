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
struct task_struct {int dummy; } ;
struct msg_msg {int dummy; } ;
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kern_ipc_perm*,struct msg_msg*,struct task_struct*,long,int) ; 
 int /*<<< orphan*/  msg_queue_msgrcv ; 

int security_msg_queue_msgrcv(struct kern_ipc_perm *msq, struct msg_msg *msg,
			       struct task_struct *target, long type, int mode)
{
	return call_int_hook(msg_queue_msgrcv, 0, msq, msg, target, type, mode);
}