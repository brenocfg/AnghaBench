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
struct tomoyo_task {int /*<<< orphan*/  domain_info; int /*<<< orphan*/  old_domain_info; } ;
struct linux_binprm {TYPE_1__* file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  current ; 
 int tomoyo_check_open_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tomoyo_find_next_domain (struct linux_binprm*) ; 
 int tomoyo_read_lock () ; 
 int /*<<< orphan*/  tomoyo_read_unlock (int const) ; 
 struct tomoyo_task* tomoyo_task (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tomoyo_bprm_check_security(struct linux_binprm *bprm)
{
	struct tomoyo_task *s = tomoyo_task(current);

	/*
	 * Execute permission is checked against pathname passed to do_execve()
	 * using current domain.
	 */
	if (!s->old_domain_info) {
		const int idx = tomoyo_read_lock();
		const int err = tomoyo_find_next_domain(bprm);

		tomoyo_read_unlock(idx);
		return err;
	}
	/*
	 * Read permission is checked against interpreters using next domain.
	 */
	return tomoyo_check_open_permission(s->domain_info,
					    &bprm->file->f_path, O_RDONLY);
}