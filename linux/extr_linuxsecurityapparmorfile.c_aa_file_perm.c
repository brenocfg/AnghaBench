#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; scalar_t__ mnt; } ;
struct file {TYPE_1__ f_path; } ;
struct aa_label {int dummy; } ;
struct aa_file_ctx {int allow; int /*<<< orphan*/  label; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int __file_path_perm (char const*,struct aa_label*,struct aa_label*,struct file*,int,int) ; 
 int __file_sock_perm (char const*,struct aa_label*,struct aa_label*,struct file*,int,int) ; 
 scalar_t__ aa_label_is_subset (struct aa_label*,struct aa_label*) ; 
 struct aa_file_ctx* file_ctx (struct file*) ; 
 TYPE_2__* file_inode (struct file*) ; 
 scalar_t__ path_mediated_fs (int /*<<< orphan*/ ) ; 
 struct aa_label* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unconfined (struct aa_label*) ; 

int aa_file_perm(const char *op, struct aa_label *label, struct file *file,
		 u32 request)
{
	struct aa_file_ctx *fctx;
	struct aa_label *flabel;
	u32 denied;
	int error = 0;

	AA_BUG(!label);
	AA_BUG(!file);

	fctx = file_ctx(file);

	rcu_read_lock();
	flabel  = rcu_dereference(fctx->label);
	AA_BUG(!flabel);

	/* revalidate access, if task is unconfined, or the cached cred
	 * doesn't match or if the request is for more permissions than
	 * was granted.
	 *
	 * Note: the test for !unconfined(flabel) is to handle file
	 *       delegation from unconfined tasks
	 */
	denied = request & ~fctx->allow;
	if (unconfined(label) || unconfined(flabel) ||
	    (!denied && aa_label_is_subset(flabel, label)))
		goto done;

	/* TODO: label cross check */

	if (file->f_path.mnt && path_mediated_fs(file->f_path.dentry))
		error = __file_path_perm(op, label, flabel, file, request,
					 denied);

	else if (S_ISSOCK(file_inode(file)->i_mode))
		error = __file_sock_perm(op, label, flabel, file, request,
					 denied);
done:
	rcu_read_unlock();

	return error;
}