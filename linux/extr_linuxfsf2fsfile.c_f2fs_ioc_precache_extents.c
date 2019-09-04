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
 int f2fs_precache_extents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 

__attribute__((used)) static int f2fs_ioc_precache_extents(struct file *filp, unsigned long arg)
{
	return f2fs_precache_extents(file_inode(filp));
}