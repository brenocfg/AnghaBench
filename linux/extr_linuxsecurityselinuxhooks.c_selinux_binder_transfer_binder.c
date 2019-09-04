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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER__TRANSFER ; 
 int /*<<< orphan*/  SECCLASS_BINDER ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static int selinux_binder_transfer_binder(struct task_struct *from,
					  struct task_struct *to)
{
	u32 fromsid = task_sid(from);
	u32 tosid = task_sid(to);

	return avc_has_perm(&selinux_state,
			    fromsid, tosid, SECCLASS_BINDER, BINDER__TRANSFER,
			    NULL);
}