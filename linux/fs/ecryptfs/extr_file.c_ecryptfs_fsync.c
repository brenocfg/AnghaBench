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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_file_to_lower (struct file*) ; 
 int file_write_and_wait (struct file*) ; 
 int vfs_fsync (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ecryptfs_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	int rc;

	rc = file_write_and_wait(file);
	if (rc)
		return rc;

	return vfs_fsync(ecryptfs_file_to_lower(file), datasync);
}