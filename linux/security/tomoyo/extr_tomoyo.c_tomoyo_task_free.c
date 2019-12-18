#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tomoyo_task {TYPE_2__* old_domain_info; TYPE_1__* domain_info; } ;
struct task_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  users; } ;
struct TYPE_3__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct tomoyo_task* tomoyo_task (struct task_struct*) ; 

__attribute__((used)) static void tomoyo_task_free(struct task_struct *task)
{
	struct tomoyo_task *s = tomoyo_task(task);

	if (s->domain_info) {
		atomic_dec(&s->domain_info->users);
		s->domain_info = NULL;
	}
	if (s->old_domain_info) {
		atomic_dec(&s->old_domain_info->users);
		s->old_domain_info = NULL;
	}
}