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
 unsigned long EBADF ; 
 unsigned long MAP_ANONYMOUS ; 
 unsigned long MAP_DENYWRITE ; 
 unsigned long MAP_EXECUTABLE ; 
 int /*<<< orphan*/  audit_mmap_fd (unsigned long,unsigned long) ; 
 struct file* fget (unsigned long) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 unsigned long vm_mmap_pgoff (struct file*,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

unsigned long ksys_mmap_pgoff(unsigned long addr, unsigned long len,
			      unsigned long prot, unsigned long flags,
			      unsigned long fd, unsigned long pgoff)
{
	struct file *file = NULL;
	unsigned long retval = -EBADF;

	audit_mmap_fd(fd, flags);
	if (!(flags & MAP_ANONYMOUS)) {
		file = fget(fd);
		if (!file)
			goto out;
	}

	flags &= ~(MAP_EXECUTABLE | MAP_DENYWRITE);

	retval = vm_mmap_pgoff(file, addr, len, prot, flags, pgoff);

	if (file)
		fput(file);
out:
	return retval;
}