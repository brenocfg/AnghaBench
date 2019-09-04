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
struct file {struct btrfs_file_private* private_data; } ;
struct btrfs_file_private {void* filldir_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct btrfs_file_private*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_opendir(struct inode *inode, struct file *file)
{
	struct btrfs_file_private *private;

	private = kzalloc(sizeof(struct btrfs_file_private), GFP_KERNEL);
	if (!private)
		return -ENOMEM;
	private->filldir_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!private->filldir_buf) {
		kfree(private);
		return -ENOMEM;
	}
	file->private_data = private;
	return 0;
}