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
struct inode {int /*<<< orphan*/  i_data; int /*<<< orphan*/ * i_mapping; int /*<<< orphan*/  i_sb; } ;
struct file {unsigned short f_flags; int /*<<< orphan*/ * private_data; TYPE_1__* f_cred; } ;
struct coda_inode_info {int /*<<< orphan*/  c_lock; scalar_t__ c_mapcount; } ;
struct coda_file_info {int /*<<< orphan*/  cfi_container; scalar_t__ cfi_mapcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 struct coda_inode_info* ITOC (struct inode*) ; 
 unsigned short O_EXCL ; 
 unsigned short coda_flags_to_cflags (unsigned short) ; 
 struct coda_file_info* coda_ftoc (struct file*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int venus_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 

int coda_release(struct inode *coda_inode, struct file *coda_file)
{
	unsigned short flags = (coda_file->f_flags) & (~O_EXCL);
	unsigned short coda_flags = coda_flags_to_cflags(flags);
	struct coda_file_info *cfi;
	struct coda_inode_info *cii;
	struct inode *host_inode;
	int err;

	cfi = coda_ftoc(coda_file);

	err = venus_close(coda_inode->i_sb, coda_i2f(coda_inode),
			  coda_flags, coda_file->f_cred->fsuid);

	host_inode = file_inode(cfi->cfi_container);
	cii = ITOC(coda_inode);

	/* did we mmap this file? */
	spin_lock(&cii->c_lock);
	if (coda_inode->i_mapping == &host_inode->i_data) {
		cii->c_mapcount -= cfi->cfi_mapcount;
		if (!cii->c_mapcount)
			coda_inode->i_mapping = &coda_inode->i_data;
	}
	spin_unlock(&cii->c_lock);

	fput(cfi->cfi_container);
	kfree(coda_file->private_data);
	coda_file->private_data = NULL;

	/* VFS fput ignores the return value from file_operations->release, so
	 * there is no use returning an error here */
	return 0;
}