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
struct mmpin {TYPE_1__* user; int /*<<< orphan*/  num_pg; } ;
struct TYPE_2__ {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (TYPE_1__*) ; 

void mm_unaccount_pinned_pages(struct mmpin *mmp)
{
	if (mmp->user) {
		atomic_long_sub(mmp->num_pg, &mmp->user->locked_vm);
		free_uid(mmp->user);
	}
}