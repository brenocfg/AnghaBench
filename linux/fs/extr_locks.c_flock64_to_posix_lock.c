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
struct flock64 {int l_whence; scalar_t__ l_start; int l_len; int /*<<< orphan*/  l_type; } ;
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/ * fl_ops; int /*<<< orphan*/  fl_flags; struct file* fl_file; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_owner; } ;
struct file {scalar_t__ f_pos; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  FL_POSIX ; 
 scalar_t__ OFFSET_MAX ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int assign_type (struct file_lock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flock64_to_posix_lock(struct file *filp, struct file_lock *fl,
				 struct flock64 *l)
{
	switch (l->l_whence) {
	case SEEK_SET:
		fl->fl_start = 0;
		break;
	case SEEK_CUR:
		fl->fl_start = filp->f_pos;
		break;
	case SEEK_END:
		fl->fl_start = i_size_read(file_inode(filp));
		break;
	default:
		return -EINVAL;
	}
	if (l->l_start > OFFSET_MAX - fl->fl_start)
		return -EOVERFLOW;
	fl->fl_start += l->l_start;
	if (fl->fl_start < 0)
		return -EINVAL;

	/* POSIX-1996 leaves the case l->l_len < 0 undefined;
	   POSIX-2001 defines it. */
	if (l->l_len > 0) {
		if (l->l_len - 1 > OFFSET_MAX - fl->fl_start)
			return -EOVERFLOW;
		fl->fl_end = fl->fl_start + l->l_len - 1;

	} else if (l->l_len < 0) {
		if (fl->fl_start + l->l_len < 0)
			return -EINVAL;
		fl->fl_end = fl->fl_start - 1;
		fl->fl_start += l->l_len;
	} else
		fl->fl_end = OFFSET_MAX;

	fl->fl_owner = current->files;
	fl->fl_pid = current->tgid;
	fl->fl_file = filp;
	fl->fl_flags = FL_POSIX;
	fl->fl_ops = NULL;
	fl->fl_lmops = NULL;

	return assign_type(fl, l->l_type);
}