#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct perf_addr_filter {unsigned long offset; unsigned long size; TYPE_1__ path; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ file_inode (struct file*) ; 

__attribute__((used)) static bool perf_addr_filter_match(struct perf_addr_filter *filter,
				     struct file *file, unsigned long offset,
				     unsigned long size)
{
	/* d_inode(NULL) won't be equal to any mapped user-space file */
	if (!filter->path.dentry)
		return false;

	if (d_inode(filter->path.dentry) != file_inode(file))
		return false;

	if (filter->offset > offset + size)
		return false;

	if (filter->offset + filter->size < offset)
		return false;

	return true;
}