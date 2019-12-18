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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  cifs_file_vm_ops ; 
 int cifs_zap_mapping (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  free_xid (int) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int get_xid () ; 

int cifs_file_strict_mmap(struct file *file, struct vm_area_struct *vma)
{
	int xid, rc = 0;
	struct inode *inode = file_inode(file);

	xid = get_xid();

	if (!CIFS_CACHE_READ(CIFS_I(inode)))
		rc = cifs_zap_mapping(inode);
	if (!rc)
		rc = generic_file_mmap(file, vma);
	if (!rc)
		vma->vm_ops = &cifs_file_vm_ops;

	free_xid(xid);
	return rc;
}