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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cifs_file_vm_ops ; 
 int cifs_revalidate_file (struct file*) ; 
 int /*<<< orphan*/  free_xid (int) ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int get_xid () ; 

int cifs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	int rc, xid;

	xid = get_xid();

	rc = cifs_revalidate_file(file);
	if (rc)
		cifs_dbg(FYI, "Validation prior to mmap failed, error=%d\n",
			 rc);
	if (!rc)
		rc = generic_file_mmap(file, vma);
	if (!rc)
		vma->vm_ops = &cifs_file_vm_ops;

	free_xid(xid);
	return rc;
}