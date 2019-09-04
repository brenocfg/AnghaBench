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
struct cred {int dummy; } ;

/* Variables and functions */
 unsigned int LSM_PRLIMIT_READ ; 
 unsigned int LSM_PRLIMIT_WRITE ; 
 int /*<<< orphan*/  PROCESS__GETRLIMIT ; 
 int /*<<< orphan*/  PROCESS__SETRLIMIT ; 
 int /*<<< orphan*/  SECCLASS_PROCESS ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cred_sid (struct cred const*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_task_prlimit(const struct cred *cred, const struct cred *tcred,
				unsigned int flags)
{
	u32 av = 0;

	if (!flags)
		return 0;
	if (flags & LSM_PRLIMIT_WRITE)
		av |= PROCESS__SETRLIMIT;
	if (flags & LSM_PRLIMIT_READ)
		av |= PROCESS__GETRLIMIT;
	return avc_has_perm(&selinux_state,
			    cred_sid(cred), cred_sid(tcred),
			    SECCLASS_PROCESS, av, NULL);
}