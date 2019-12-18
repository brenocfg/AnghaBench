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
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM_FLAG_ANY ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
#define  SEEK_CUR 132 
#define  SEEK_DATA 131 
#define  SEEK_END 130 
#define  SEEK_HOLE 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  generic_file_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_seek_data (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_seek_hole (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t gfs2_llseek(struct file *file, loff_t offset, int whence)
{
	struct gfs2_inode *ip = GFS2_I(file->f_mapping->host);
	struct gfs2_holder i_gh;
	loff_t error;

	switch (whence) {
	case SEEK_END:
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY,
					   &i_gh);
		if (!error) {
			error = generic_file_llseek(file, offset, whence);
			gfs2_glock_dq_uninit(&i_gh);
		}
		break;

	case SEEK_DATA:
		error = gfs2_seek_data(file, offset);
		break;

	case SEEK_HOLE:
		error = gfs2_seek_hole(file, offset);
		break;

	case SEEK_CUR:
	case SEEK_SET:
		/*
		 * These don't reference inode->i_size and don't depend on the
		 * block mapping, so we don't need the glock.
		 */
		error = generic_file_llseek(file, offset, whence);
		break;
	default:
		error = -EINVAL;
	}

	return error;
}