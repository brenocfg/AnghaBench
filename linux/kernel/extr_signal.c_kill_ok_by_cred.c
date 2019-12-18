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
struct cred {int /*<<< orphan*/  user_ns; int /*<<< orphan*/  uid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_KILL ; 
 struct cred* __task_cred (struct task_struct*) ; 
 struct cred* current_cred () ; 
 scalar_t__ ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kill_ok_by_cred(struct task_struct *t)
{
	const struct cred *cred = current_cred();
	const struct cred *tcred = __task_cred(t);

	return uid_eq(cred->euid, tcred->suid) ||
	       uid_eq(cred->euid, tcred->uid) ||
	       uid_eq(cred->uid, tcred->suid) ||
	       uid_eq(cred->uid, tcred->uid) ||
	       ns_capable(tcred->user_ns, CAP_KILL);
}