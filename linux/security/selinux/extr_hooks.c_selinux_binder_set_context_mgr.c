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
 int /*<<< orphan*/  BINDER__SET_CONTEXT_MGR ; 
 int /*<<< orphan*/  SECCLASS_BINDER ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static int selinux_binder_set_context_mgr(struct task_struct *mgr)
{
	u32 mysid = current_sid();
	u32 mgrsid = task_sid(mgr);

	return avc_has_perm(&selinux_state,
			    mysid, mgrsid, SECCLASS_BINDER,
			    BINDER__SET_CONTEXT_MGR, NULL);
}