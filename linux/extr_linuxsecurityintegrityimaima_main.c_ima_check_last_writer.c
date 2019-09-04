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
struct integrity_iint_cache {int flags; int /*<<< orphan*/  mutex; scalar_t__ measured_pcrs; int /*<<< orphan*/  version; int /*<<< orphan*/  atomic_flags; } ;
struct inode {int /*<<< orphan*/  i_writecount; } ;
struct file {int f_mode; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int IMA_DONE_MASK ; 
 int IMA_NEW_FILE ; 
 int /*<<< orphan*/  IMA_UPDATE_XATTR ; 
 int /*<<< orphan*/  IS_I_VERSION (struct inode*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ima_update_xattr (struct integrity_iint_cache*,struct file*) ; 
 int /*<<< orphan*/  inode_eq_iversion (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ima_check_last_writer(struct integrity_iint_cache *iint,
				  struct inode *inode, struct file *file)
{
	fmode_t mode = file->f_mode;
	bool update;

	if (!(mode & FMODE_WRITE))
		return;

	mutex_lock(&iint->mutex);
	if (atomic_read(&inode->i_writecount) == 1) {
		update = test_and_clear_bit(IMA_UPDATE_XATTR,
					    &iint->atomic_flags);
		if (!IS_I_VERSION(inode) ||
		    !inode_eq_iversion(inode, iint->version) ||
		    (iint->flags & IMA_NEW_FILE)) {
			iint->flags &= ~(IMA_DONE_MASK | IMA_NEW_FILE);
			iint->measured_pcrs = 0;
			if (update)
				ima_update_xattr(iint, file);
		}
	}
	mutex_unlock(&iint->mutex);
}