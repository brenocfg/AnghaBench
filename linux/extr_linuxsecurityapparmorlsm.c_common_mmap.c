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
 int AA_EXEC_MMAP ; 
 unsigned long MAP_PRIVATE ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 unsigned long PROT_EXEC ; 
 unsigned long PROT_READ ; 
 unsigned long PROT_WRITE ; 
 int common_file_perm (char const*,struct file*,int) ; 
 int /*<<< orphan*/  file_ctx (struct file*) ; 

__attribute__((used)) static int common_mmap(const char *op, struct file *file, unsigned long prot,
		       unsigned long flags)
{
	int mask = 0;

	if (!file || !file_ctx(file))
		return 0;

	if (prot & PROT_READ)
		mask |= MAY_READ;
	/*
	 * Private mappings don't require write perms since they don't
	 * write back to the files
	 */
	if ((prot & PROT_WRITE) && !(flags & MAP_PRIVATE))
		mask |= MAY_WRITE;
	if (prot & PROT_EXEC)
		mask |= AA_EXEC_MMAP;

	return common_file_perm(op, file, mask);
}