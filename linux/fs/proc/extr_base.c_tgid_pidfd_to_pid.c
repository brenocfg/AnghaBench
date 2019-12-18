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
struct pid {int dummy; } ;
struct file {int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 struct pid* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file const*) ; 
 struct pid* proc_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_tgid_base_operations ; 

struct pid *tgid_pidfd_to_pid(const struct file *file)
{
	if (file->f_op != &proc_tgid_base_operations)
		return ERR_PTR(-EBADF);

	return proc_pid(file_inode(file));
}