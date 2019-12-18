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
struct kernel_siginfo {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESS__SIGNULL ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 
 int /*<<< orphan*/  current_sid () ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  signal_to_av (int) ; 
 int /*<<< orphan*/  task_sid (struct task_struct*) ; 

__attribute__((used)) static int selinux_task_kill(struct task_struct *p, struct kernel_siginfo *info,
				int sig, const struct cred *cred)
{
	u32 secid;
	u32 perm;

	if (!sig)
		perm = PROCESS__SIGNULL; /* null signal; existence test */
	else
		perm = signal_to_av(sig);
	if (!cred)
		secid = current_sid();
	else
		secid = cred_sid(cred);
	return avc_has_perm(&selinux_state,
			    secid, task_sid(p), SECCLASS_PROCESS, perm, NULL);
}