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
struct mm_struct {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct mm_struct* private_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mm_struct*) ; 
 int PTR_ERR (struct mm_struct*) ; 
 struct mm_struct* proc_mem_open (struct inode*,unsigned int) ; 

__attribute__((used)) static int __mem_open(struct inode *inode, struct file *file, unsigned int mode)
{
	struct mm_struct *mm = proc_mem_open(inode, mode);

	if (IS_ERR(mm))
		return PTR_ERR(mm);

	file->private_data = mm;
	return 0;
}