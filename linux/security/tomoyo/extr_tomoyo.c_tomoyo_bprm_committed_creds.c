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
struct tomoyo_task {TYPE_1__* old_domain_info; } ;
struct linux_binprm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct tomoyo_task* tomoyo_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tomoyo_bprm_committed_creds(struct linux_binprm *bprm)
{
	/* Clear old_domain_info saved by execve() request. */
	struct tomoyo_task *s = tomoyo_task(current);

	atomic_dec(&s->old_domain_info->users);
	s->old_domain_info = NULL;
}