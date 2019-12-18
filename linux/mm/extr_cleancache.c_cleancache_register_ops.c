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
struct cleancache_ops {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  cleancache_ops ; 
 int /*<<< orphan*/  cleancache_register_ops_sb ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cleancache_ops const*) ; 
 int /*<<< orphan*/  iterate_supers (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cleancache_register_ops(const struct cleancache_ops *ops)
{
	if (cmpxchg(&cleancache_ops, NULL, ops))
		return -EBUSY;

	/*
	 * A cleancache backend can be built as a module and hence loaded after
	 * a cleancache enabled filesystem has called cleancache_init_fs. To
	 * handle such a scenario, here we call ->init_fs or ->init_shared_fs
	 * for each active super block. To differentiate between local and
	 * shared filesystems, we temporarily initialize sb->cleancache_poolid
	 * to CLEANCACHE_NO_BACKEND or CLEANCACHE_NO_BACKEND_SHARED
	 * respectively in case there is no backend registered at the time
	 * cleancache_init_fs or cleancache_init_shared_fs is called.
	 *
	 * Since filesystems can be mounted concurrently with cleancache
	 * backend registration, we have to be careful to guarantee that all
	 * cleancache enabled filesystems that has been mounted by the time
	 * cleancache_register_ops is called has got and all mounted later will
	 * get cleancache_poolid. This is assured by the following statements
	 * tied together:
	 *
	 * a) iterate_supers skips only those super blocks that has started
	 *    ->kill_sb
	 *
	 * b) if iterate_supers encounters a super block that has not finished
	 *    ->mount yet, it waits until it is finished
	 *
	 * c) cleancache_init_fs is called from ->mount and
	 *    cleancache_invalidate_fs is called from ->kill_sb
	 *
	 * d) we call iterate_supers after cleancache_ops has been set
	 *
	 * From a) it follows that if iterate_supers skips a super block, then
	 * either the super block is already dead, in which case we do not need
	 * to bother initializing cleancache for it, or it was mounted after we
	 * initiated iterate_supers. In the latter case, it must have seen
	 * cleancache_ops set according to d) and initialized cleancache from
	 * ->mount by itself according to c). This proves that we call
	 * ->init_fs at least once for each active super block.
	 *
	 * From b) and c) it follows that if iterate_supers encounters a super
	 * block that has already started ->init_fs, it will wait until ->mount
	 * and hence ->init_fs has finished, then check cleancache_poolid, see
	 * that it has already been set and therefore do nothing. This proves
	 * that we call ->init_fs no more than once for each super block.
	 *
	 * Combined together, the last two paragraphs prove the function
	 * correctness.
	 *
	 * Note that various cleancache callbacks may proceed before this
	 * function is called or even concurrently with it, but since
	 * CLEANCACHE_NO_BACKEND is negative, they will all result in a noop
	 * until the corresponding ->init_fs has been actually called and
	 * cleancache_ops has been set.
	 */
	iterate_supers(cleancache_register_ops_sb, NULL);
	return 0;
}