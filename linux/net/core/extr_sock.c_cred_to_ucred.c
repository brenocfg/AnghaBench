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
struct user_namespace {int dummy; } ;
struct ucred {int uid; int gid; int /*<<< orphan*/  pid; } ;
struct pid {int dummy; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 struct user_namespace* current_user_ns () ; 
 int from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_vnr (struct pid*) ; 

__attribute__((used)) static void cred_to_ucred(struct pid *pid, const struct cred *cred,
			  struct ucred *ucred)
{
	ucred->pid = pid_vnr(pid);
	ucred->uid = ucred->gid = -1;
	if (cred) {
		struct user_namespace *current_ns = current_user_ns();

		ucred->uid = from_kuid_munged(current_ns, cred->euid);
		ucred->gid = from_kgid_munged(current_ns, cred->egid);
	}
}