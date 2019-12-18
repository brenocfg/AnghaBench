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
 int /*<<< orphan*/  vfs_llseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static loff_t ecryptfs_dir_llseek(struct file *file, loff_t offset, int whence)
{
	return vfs_llseek(ecryptfs_file_to_lower(file), offset, whence);
}