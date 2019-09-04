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
typedef  unsigned long u64 ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long file_mmap_size_max (struct file*,struct inode*) ; 

__attribute__((used)) static inline bool file_mmap_ok(struct file *file, struct inode *inode,
				unsigned long pgoff, unsigned long len)
{
	u64 maxsize = file_mmap_size_max(file, inode);

	if (maxsize && len > maxsize)
		return false;
	maxsize -= len;
	if (pgoff > maxsize >> PAGE_SHIFT)
		return false;
	return true;
}