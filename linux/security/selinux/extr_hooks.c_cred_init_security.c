#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_security_struct {int /*<<< orphan*/  sid; int /*<<< orphan*/  osid; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {scalar_t__ real_cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECINITSID_KERNEL ; 
 TYPE_1__* current ; 
 struct task_security_struct* selinux_cred (struct cred*) ; 

__attribute__((used)) static void cred_init_security(void)
{
	struct cred *cred = (struct cred *) current->real_cred;
	struct task_security_struct *tsec;

	tsec = selinux_cred(cred);
	tsec->osid = tsec->sid = SECINITSID_KERNEL;
}