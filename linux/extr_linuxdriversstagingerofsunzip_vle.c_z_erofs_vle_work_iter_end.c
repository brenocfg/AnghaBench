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
struct z_erofs_vle_work_builder {int /*<<< orphan*/ * grp; struct z_erofs_vle_work* work; int /*<<< orphan*/  hosted; int /*<<< orphan*/  vector; } ;
struct z_erofs_vle_work {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __z_erofs_vle_work_release (int /*<<< orphan*/ *,struct z_erofs_vle_work*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z_erofs_pagevec_ctor_exit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline bool
z_erofs_vle_work_iter_end(struct z_erofs_vle_work_builder *builder)
{
	struct z_erofs_vle_work *work = builder->work;

	if (work == NULL)
		return false;

	z_erofs_pagevec_ctor_exit(&builder->vector, false);
	mutex_unlock(&work->lock);

	/*
	 * if all pending pages are added, don't hold work reference
	 * any longer if the current work isn't hosted by ourselves.
	 */
	if (!builder->hosted)
		__z_erofs_vle_work_release(builder->grp, work);

	builder->work = NULL;
	builder->grp = NULL;
	return true;
}