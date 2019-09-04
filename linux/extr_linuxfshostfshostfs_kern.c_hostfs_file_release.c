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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostfs_file_release(struct inode *inode, struct file *file)
{
	filemap_write_and_wait(inode->i_mapping);

	return 0;
}