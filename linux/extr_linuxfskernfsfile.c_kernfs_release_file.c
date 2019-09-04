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
struct kernfs_open_file {int released; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct kernfs_node {TYPE_2__ attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct kernfs_open_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_open_file_mutex ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kernfs_open_file*) ; 

__attribute__((used)) static void kernfs_release_file(struct kernfs_node *kn,
				struct kernfs_open_file *of)
{
	/*
	 * @of is guaranteed to have no other file operations in flight and
	 * we just want to synchronize release and drain paths.
	 * @kernfs_open_file_mutex is enough.  @of->mutex can't be used
	 * here because drain path may be called from places which can
	 * cause circular dependency.
	 */
	lockdep_assert_held(&kernfs_open_file_mutex);

	if (!of->released) {
		/*
		 * A file is never detached without being released and we
		 * need to be able to release files which are deactivated
		 * and being drained.  Don't use kernfs_ops().
		 */
		kn->attr.ops->release(of);
		of->released = true;
	}
}