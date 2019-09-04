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
struct pnfs_block_layout {int /*<<< orphan*/  bl_ext_lock; int /*<<< orphan*/  bl_ext_rw; int /*<<< orphan*/  bl_ext_ro; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ext_put_deviceids (int /*<<< orphan*/ *) ; 
 int __ext_tree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp ; 

int ext_tree_remove(struct pnfs_block_layout *bl, bool rw,
		sector_t start, sector_t end)
{
	int err, err2;
	LIST_HEAD(tmp);

	spin_lock(&bl->bl_ext_lock);
	err = __ext_tree_remove(&bl->bl_ext_ro, start, end, &tmp);
	if (rw) {
		err2 = __ext_tree_remove(&bl->bl_ext_rw, start, end, &tmp);
		if (!err)
			err = err2;
	}
	spin_unlock(&bl->bl_ext_lock);

	__ext_put_deviceids(&tmp);
	return err;
}