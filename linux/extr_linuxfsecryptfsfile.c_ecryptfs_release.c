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

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_file_info_cache ; 
 int /*<<< orphan*/  ecryptfs_file_to_private (struct file*) ; 
 int /*<<< orphan*/  ecryptfs_put_lower_file (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecryptfs_release(struct inode *inode, struct file *file)
{
	ecryptfs_put_lower_file(inode);
	kmem_cache_free(ecryptfs_file_info_cache,
			ecryptfs_file_to_private(file));
	return 0;
}