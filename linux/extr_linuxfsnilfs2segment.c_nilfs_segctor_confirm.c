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
struct the_nilfs {int /*<<< orphan*/  ns_inode_lock; int /*<<< orphan*/  ns_dirty_files; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_root; TYPE_1__* sc_super; } ;
struct TYPE_2__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SC_DIRTY ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ nilfs_segctor_clean (struct nilfs_sc_info*) ; 
 scalar_t__ nilfs_test_metadata_dirty (struct the_nilfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segctor_confirm(struct nilfs_sc_info *sci)
{
	struct the_nilfs *nilfs = sci->sc_super->s_fs_info;
	int ret = 0;

	if (nilfs_test_metadata_dirty(nilfs, sci->sc_root))
		set_bit(NILFS_SC_DIRTY, &sci->sc_flags);

	spin_lock(&nilfs->ns_inode_lock);
	if (list_empty(&nilfs->ns_dirty_files) && nilfs_segctor_clean(sci))
		ret++;

	spin_unlock(&nilfs->ns_inode_lock);
	return ret;
}