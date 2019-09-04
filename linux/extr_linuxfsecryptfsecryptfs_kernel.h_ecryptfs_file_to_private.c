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
struct file {struct ecryptfs_file_info* private_data; } ;
struct ecryptfs_file_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ecryptfs_file_info *
ecryptfs_file_to_private(struct file *file)
{
	return file->private_data;
}