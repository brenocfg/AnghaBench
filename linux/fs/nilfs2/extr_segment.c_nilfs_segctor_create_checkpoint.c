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
struct the_nilfs {int /*<<< orphan*/  ns_cno; int /*<<< orphan*/  ns_cpfile; } ;
struct nilfs_sc_info {TYPE_1__* sc_super; } ;
struct nilfs_checkpoint {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int nilfs_cpfile_get_checkpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nilfs_checkpoint**,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_cpfile_put_checkpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_segctor_create_checkpoint(struct nilfs_sc_info *sci)
{
	struct the_nilfs *nilfs = sci->sc_super->s_fs_info;
	struct buffer_head *bh_cp;
	struct nilfs_checkpoint *raw_cp;
	int err;

	/* XXX: this interface will be changed */
	err = nilfs_cpfile_get_checkpoint(nilfs->ns_cpfile, nilfs->ns_cno, 1,
					  &raw_cp, &bh_cp);
	if (likely(!err)) {
		/*
		 * The following code is duplicated with cpfile.  But, it is
		 * needed to collect the checkpoint even if it was not newly
		 * created.
		 */
		mark_buffer_dirty(bh_cp);
		nilfs_mdt_mark_dirty(nilfs->ns_cpfile);
		nilfs_cpfile_put_checkpoint(
			nilfs->ns_cpfile, nilfs->ns_cno, bh_cp);
	} else
		WARN_ON(err == -EINVAL || err == -ENOENT);

	return err;
}