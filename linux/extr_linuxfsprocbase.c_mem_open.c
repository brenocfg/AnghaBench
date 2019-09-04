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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  f_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_UNSIGNED_OFFSET ; 
 int /*<<< orphan*/  PTRACE_MODE_ATTACH ; 
 int __mem_open (struct inode*,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mem_open(struct inode *inode, struct file *file)
{
	int ret = __mem_open(inode, file, PTRACE_MODE_ATTACH);

	/* OK to pass negative loff_t, we can catch out-of-range */
	file->f_mode |= FMODE_UNSIGNED_OFFSET;

	return ret;
}