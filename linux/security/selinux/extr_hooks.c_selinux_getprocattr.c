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
struct task_security_struct {int /*<<< orphan*/  sockcreate_sid; int /*<<< orphan*/  keycreate_sid; int /*<<< orphan*/  create_sid; int /*<<< orphan*/  exec_sid; int /*<<< orphan*/  osid; int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PROCESS__GETATTR ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int /*<<< orphan*/  __task_cred (struct task_struct*) ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int security_sid_to_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,unsigned int*) ; 
 struct task_security_struct* selinux_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int selinux_getprocattr(struct task_struct *p,
			       char *name, char **value)
{
	const struct task_security_struct *__tsec;
	u32 sid;
	int error;
	unsigned len;

	rcu_read_lock();
	__tsec = selinux_cred(__task_cred(p));

	if (current != p) {
		error = avc_has_perm(&selinux_state,
				     current_sid(), __tsec->sid,
				     SECCLASS_PROCESS, PROCESS__GETATTR, NULL);
		if (error)
			goto bad;
	}

	if (!strcmp(name, "current"))
		sid = __tsec->sid;
	else if (!strcmp(name, "prev"))
		sid = __tsec->osid;
	else if (!strcmp(name, "exec"))
		sid = __tsec->exec_sid;
	else if (!strcmp(name, "fscreate"))
		sid = __tsec->create_sid;
	else if (!strcmp(name, "keycreate"))
		sid = __tsec->keycreate_sid;
	else if (!strcmp(name, "sockcreate"))
		sid = __tsec->sockcreate_sid;
	else {
		error = -EINVAL;
		goto bad;
	}
	rcu_read_unlock();

	if (!sid)
		return 0;

	error = security_sid_to_context(&selinux_state, sid, value, &len);
	if (error)
		return error;
	return len;

bad:
	rcu_read_unlock();
	return error;
}