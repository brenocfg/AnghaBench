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
struct file {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int ima_file_mmap (struct file*,unsigned long) ; 
 int /*<<< orphan*/  mmap_file ; 
 int /*<<< orphan*/  mmap_prot (struct file*,unsigned long) ; 

int security_mmap_file(struct file *file, unsigned long prot,
			unsigned long flags)
{
	int ret;
	ret = call_int_hook(mmap_file, 0, file, prot,
					mmap_prot(file, prot), flags);
	if (ret)
		return ret;
	return ima_file_mmap(file, prot);
}