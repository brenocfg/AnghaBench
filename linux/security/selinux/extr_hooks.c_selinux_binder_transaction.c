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
typedef  scalar_t__ u32 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER__CALL ; 
 int /*<<< orphan*/  BINDER__IMPERSONATE ; 
 int /*<<< orphan*/  SECCLASS_BINDER ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ current_sid () ; 
 int /*<<< orphan*/  selinux_state ; 
 scalar_t__ task_sid (struct task_struct*) ; 

__attribute__((used)) static int selinux_binder_transaction(struct task_struct *from,
				      struct task_struct *to)
{
	u32 mysid = current_sid();
	u32 fromsid = task_sid(from);
	u32 tosid = task_sid(to);
	int rc;

	if (mysid != fromsid) {
		rc = avc_has_perm(&selinux_state,
				  mysid, fromsid, SECCLASS_BINDER,
				  BINDER__IMPERSONATE, NULL);
		if (rc)
			return rc;
	}

	return avc_has_perm(&selinux_state,
			    fromsid, tosid, SECCLASS_BINDER, BINDER__CALL,
			    NULL);
}