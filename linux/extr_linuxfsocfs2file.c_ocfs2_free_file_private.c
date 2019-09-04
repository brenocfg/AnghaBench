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
struct ocfs2_super {int dummy; } ;
struct ocfs2_file_private {int /*<<< orphan*/  fp_flock; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {struct ocfs2_file_private* private_data; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_file_private*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (struct ocfs2_super*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_free_file_private(struct inode *inode, struct file *file)
{
	struct ocfs2_file_private *fp = file->private_data;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (fp) {
		ocfs2_simple_drop_lockres(osb, &fp->fp_flock);
		ocfs2_lock_res_free(&fp->fp_flock);
		kfree(fp);
		file->private_data = NULL;
	}
}