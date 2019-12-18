#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tomoyo_task {struct tomoyo_domain_info* domain_info; TYPE_1__* old_domain_info; } ;
struct tomoyo_domain_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  in_execve; } ;
struct TYPE_4__ {int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 struct tomoyo_task* tomoyo_task (TYPE_2__*) ; 

struct tomoyo_domain_info *tomoyo_domain(void)
{
	struct tomoyo_task *s = tomoyo_task(current);

	if (s->old_domain_info && !current->in_execve) {
		atomic_dec(&s->old_domain_info->users);
		s->old_domain_info = NULL;
	}
	return s->domain_info;
}