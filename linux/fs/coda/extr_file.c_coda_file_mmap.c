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
struct vm_area_struct {size_t vm_end; size_t vm_start; int vm_pgoff; TYPE_2__* vm_ops; struct file* vm_file; } ;
struct inode {int /*<<< orphan*/ * i_mapping; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_sb; } ;
struct file {int /*<<< orphan*/  f_mapping; TYPE_1__* f_op; } ;
struct TYPE_4__ {int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;
struct coda_vm_ops {TYPE_2__ vm_ops; int /*<<< orphan*/  refcnt; struct file* coda_file; TYPE_2__* host_vm_ops; } ;
struct coda_inode_info {int /*<<< orphan*/  c_lock; int /*<<< orphan*/  c_mapcount; } ;
struct coda_file_info {int /*<<< orphan*/  cfi_mapcount; int /*<<< orphan*/  cfi_access_intent; struct file* cfi_container; } ;
typedef  int loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_ACCESS_TYPE_MMAP ; 
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct coda_inode_info* ITOC (struct inode*) ; 
 int PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int call_mmap (struct file*,struct vm_area_struct*) ; 
 struct coda_file_info* coda_ftoc (struct file*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 int /*<<< orphan*/  coda_vm_close ; 
 int /*<<< orphan*/  coda_vm_open ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_file (struct file*) ; 
 int /*<<< orphan*/  kfree (struct coda_vm_ops*) ; 
 struct coda_vm_ops* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int venus_access_intent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
coda_file_mmap(struct file *coda_file, struct vm_area_struct *vma)
{
	struct inode *coda_inode = file_inode(coda_file);
	struct coda_file_info *cfi = coda_ftoc(coda_file);
	struct file *host_file = cfi->cfi_container;
	struct inode *host_inode = file_inode(host_file);
	struct coda_inode_info *cii;
	struct coda_vm_ops *cvm_ops;
	loff_t ppos;
	size_t count;
	int ret;

	if (!host_file->f_op->mmap)
		return -ENODEV;

	if (WARN_ON(coda_file != vma->vm_file))
		return -EIO;

	count = vma->vm_end - vma->vm_start;
	ppos = vma->vm_pgoff * PAGE_SIZE;

	ret = venus_access_intent(coda_inode->i_sb, coda_i2f(coda_inode),
				  &cfi->cfi_access_intent,
				  count, ppos, CODA_ACCESS_TYPE_MMAP);
	if (ret)
		return ret;

	cvm_ops = kmalloc(sizeof(struct coda_vm_ops), GFP_KERNEL);
	if (!cvm_ops)
		return -ENOMEM;

	cii = ITOC(coda_inode);
	spin_lock(&cii->c_lock);
	coda_file->f_mapping = host_file->f_mapping;
	if (coda_inode->i_mapping == &coda_inode->i_data)
		coda_inode->i_mapping = host_inode->i_mapping;

	/* only allow additional mmaps as long as userspace isn't changing
	 * the container file on us! */
	else if (coda_inode->i_mapping != host_inode->i_mapping) {
		spin_unlock(&cii->c_lock);
		kfree(cvm_ops);
		return -EBUSY;
	}

	/* keep track of how often the coda_inode/host_file has been mmapped */
	cii->c_mapcount++;
	cfi->cfi_mapcount++;
	spin_unlock(&cii->c_lock);

	vma->vm_file = get_file(host_file);
	ret = call_mmap(vma->vm_file, vma);

	if (ret) {
		/* if call_mmap fails, our caller will put coda_file so we
		 * should drop the reference to the host_file that we got.
		 */
		fput(host_file);
		kfree(cvm_ops);
	} else {
		/* here we add redirects for the open/close vm_operations */
		cvm_ops->host_vm_ops = vma->vm_ops;
		if (vma->vm_ops)
			cvm_ops->vm_ops = *vma->vm_ops;

		cvm_ops->vm_ops.open = coda_vm_open;
		cvm_ops->vm_ops.close = coda_vm_close;
		cvm_ops->coda_file = coda_file;
		atomic_set(&cvm_ops->refcnt, 1);

		vma->vm_ops = &cvm_ops->vm_ops;
	}
	return ret;
}