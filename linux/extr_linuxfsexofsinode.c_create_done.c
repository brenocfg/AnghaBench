#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ore_io_state {int dummy; } ;
struct inode {TYPE_3__* i_sb; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_curr_pending; } ;
struct TYPE_4__ {int /*<<< orphan*/  partition; } ;
struct TYPE_5__ {TYPE_1__ obj; } ;
struct exofs_i_info {int /*<<< orphan*/  i_wq; TYPE_2__ one_comp; } ;
struct TYPE_6__ {struct exofs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _LLU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct exofs_i_info* exofs_i (struct inode*) ; 
 int /*<<< orphan*/  exofs_oi_objno (struct exofs_i_info*) ; 
 int ore_check_io (struct ore_io_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ore_put_io_state (struct ore_io_state*) ; 
 int /*<<< orphan*/  set_obj_created (struct exofs_i_info*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_done(struct ore_io_state *ios, void *p)
{
	struct inode *inode = p;
	struct exofs_i_info *oi = exofs_i(inode);
	struct exofs_sb_info *sbi = inode->i_sb->s_fs_info;
	int ret;

	ret = ore_check_io(ios, NULL);
	ore_put_io_state(ios);

	atomic_dec(&sbi->s_curr_pending);

	if (unlikely(ret)) {
		EXOFS_ERR("object=0x%llx creation failed in pid=0x%llx",
			  _LLU(exofs_oi_objno(oi)),
			  _LLU(oi->one_comp.obj.partition));
		/*TODO: When FS is corrupted creation can fail, object already
		 * exist. Get rid of this asynchronous creation, if exist
		 * increment the obj counter and try the next object. Until we
		 * succeed. All these dangling objects will be made into lost
		 * files by chkfs.exofs
		 */
	}

	set_obj_created(oi);

	wake_up(&oi->i_wq);
}