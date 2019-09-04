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
struct path_cond {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct path {struct dentry* dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;
struct aa_label {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int AA_MAY_CREATE ; 
 int AA_MAY_DELETE ; 
 int AA_MAY_GETATTR ; 
 int AA_MAY_SETATTR ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  OP_RENAME_DEST ; 
 int /*<<< orphan*/  OP_RENAME_SRC ; 
 int aa_path_perm (int /*<<< orphan*/ ,struct aa_label*,struct path*,int /*<<< orphan*/ ,int,struct path_cond*) ; 
 struct aa_label* begin_current_label_crit_section () ; 
 TYPE_1__* d_backing_inode (struct dentry*) ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 int /*<<< orphan*/  path_mediated_fs (struct dentry*) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_path_rename(const struct path *old_dir, struct dentry *old_dentry,
				const struct path *new_dir, struct dentry *new_dentry)
{
	struct aa_label *label;
	int error = 0;

	if (!path_mediated_fs(old_dentry))
		return 0;

	label = begin_current_label_crit_section();
	if (!unconfined(label)) {
		struct path old_path = { .mnt = old_dir->mnt,
					 .dentry = old_dentry };
		struct path new_path = { .mnt = new_dir->mnt,
					 .dentry = new_dentry };
		struct path_cond cond = { d_backing_inode(old_dentry)->i_uid,
					  d_backing_inode(old_dentry)->i_mode
		};

		error = aa_path_perm(OP_RENAME_SRC, label, &old_path, 0,
				     MAY_READ | AA_MAY_GETATTR | MAY_WRITE |
				     AA_MAY_SETATTR | AA_MAY_DELETE,
				     &cond);
		if (!error)
			error = aa_path_perm(OP_RENAME_DEST, label, &new_path,
					     0, MAY_WRITE | AA_MAY_SETATTR |
					     AA_MAY_CREATE, &cond);

	}
	end_current_label_crit_section(label);

	return error;
}