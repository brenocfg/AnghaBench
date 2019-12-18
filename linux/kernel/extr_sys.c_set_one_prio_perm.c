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
struct cred {int /*<<< orphan*/  user_ns; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 struct cred* __task_cred (struct task_struct*) ; 
 struct cred* current_cred () ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_one_prio_perm(struct task_struct *p)
{
	const struct cred *cred = current_cred(), *pcred = __task_cred(p);

	if (uid_eq(pcred->uid,  cred->euid) ||
	    uid_eq(pcred->euid, cred->euid))
		return true;
	if (ns_capable(pcred->user_ns, CAP_SYS_NICE))
		return true;
	return false;
}