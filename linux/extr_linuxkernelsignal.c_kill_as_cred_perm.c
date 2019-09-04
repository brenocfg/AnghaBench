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
struct cred {int /*<<< orphan*/  uid; int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 struct cred* __task_cred (struct task_struct*) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool kill_as_cred_perm(const struct cred *cred,
				     struct task_struct *target)
{
	const struct cred *pcred = __task_cred(target);

	return uid_eq(cred->euid, pcred->suid) ||
	       uid_eq(cred->euid, pcred->uid) ||
	       uid_eq(cred->uid, pcred->suid) ||
	       uid_eq(cred->uid, pcred->uid);
}