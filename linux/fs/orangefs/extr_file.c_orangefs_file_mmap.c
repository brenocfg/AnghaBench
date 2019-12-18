#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_flags; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
struct TYPE_4__ {scalar_t__ name; } ;
struct TYPE_5__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_FILE_DEBUG ; 
 int /*<<< orphan*/  VM_RAND_READ ; 
 int /*<<< orphan*/  VM_SEQ_READ ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  orangefs_file_vm_ops ; 
 int orangefs_revalidate_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orangefs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret;

	ret = orangefs_revalidate_mapping(file_inode(file));
	if (ret)
		return ret;

	gossip_debug(GOSSIP_FILE_DEBUG,
		     "orangefs_file_mmap: called on %s\n",
		     (file ?
			(char *)file->f_path.dentry->d_name.name :
			(char *)"Unknown"));

	/* set the sequential readahead hint */
	vma->vm_flags |= VM_SEQ_READ;
	vma->vm_flags &= ~VM_RAND_READ;

	file_accessed(file);
	vma->vm_ops = &orangefs_file_vm_ops;
	return 0;
}