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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;
struct gfs2_holder {int dummy; } ;
struct file {int f_flags; TYPE_1__* f_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_NOATIME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LM_FLAG_ANY ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int O_NOATIME ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_vm_ops ; 

__attribute__((used)) static int gfs2_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct gfs2_inode *ip = GFS2_I(file->f_mapping->host);

	if (!(file->f_flags & O_NOATIME) &&
	    !IS_NOATIME(&ip->i_inode)) {
		struct gfs2_holder i_gh;
		int error;

		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY,
					   &i_gh);
		if (error)
			return error;
		/* grab lock to update inode */
		gfs2_glock_dq_uninit(&i_gh);
		file_accessed(file);
	}
	vma->vm_ops = &gfs2_vm_ops;

	return 0;
}