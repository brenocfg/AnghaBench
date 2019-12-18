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
struct dlm_ls {int ls_uevent_result; int /*<<< orphan*/  ls_flags; int /*<<< orphan*/  ls_uevent_wait; int /*<<< orphan*/  ls_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_OFFLINE ; 
 int /*<<< orphan*/  KOBJ_ONLINE ; 
 int /*<<< orphan*/  LSFL_UEVENT_WAIT ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,char*,int,int) ; 
 int /*<<< orphan*/  log_rinfo (struct dlm_ls*,char*,...) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_uevent(struct dlm_ls *ls, int in)
{
	int error;

	if (in)
		kobject_uevent(&ls->ls_kobj, KOBJ_ONLINE);
	else
		kobject_uevent(&ls->ls_kobj, KOBJ_OFFLINE);

	log_rinfo(ls, "%s the lockspace group...", in ? "joining" : "leaving");

	/* dlm_controld will see the uevent, do the necessary group management
	   and then write to sysfs to wake us */

	error = wait_event_interruptible(ls->ls_uevent_wait,
			test_and_clear_bit(LSFL_UEVENT_WAIT, &ls->ls_flags));

	log_rinfo(ls, "group event done %d %d", error, ls->ls_uevent_result);

	if (error)
		goto out;

	error = ls->ls_uevent_result;
 out:
	if (error)
		log_error(ls, "group %s failed %d %d", in ? "join" : "leave",
			  error, ls->ls_uevent_result);
	return error;
}