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
struct file {int dummy; } ;
struct cache_detail {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EACCES ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_flush(struct inode *inode, struct file *file,
			struct cache_detail *cd)
{
	if (!cd || !try_module_get(cd->owner))
		return -EACCES;
	return nonseekable_open(inode, file);
}