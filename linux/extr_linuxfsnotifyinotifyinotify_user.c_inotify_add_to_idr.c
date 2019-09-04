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
struct inotify_inode_mark {int wd; int /*<<< orphan*/  fsn_mark; } ;
struct idr {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  fsnotify_get_mark (int /*<<< orphan*/ *) ; 
 int idr_alloc_cyclic (struct idr*,struct inotify_inode_mark*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inotify_add_to_idr(struct idr *idr, spinlock_t *idr_lock,
			      struct inotify_inode_mark *i_mark)
{
	int ret;

	idr_preload(GFP_KERNEL);
	spin_lock(idr_lock);

	ret = idr_alloc_cyclic(idr, i_mark, 1, 0, GFP_NOWAIT);
	if (ret >= 0) {
		/* we added the mark to the idr, take a reference */
		i_mark->wd = ret;
		fsnotify_get_mark(&i_mark->fsn_mark);
	}

	spin_unlock(idr_lock);
	idr_preload_end();
	return ret < 0 ? ret : 0;
}