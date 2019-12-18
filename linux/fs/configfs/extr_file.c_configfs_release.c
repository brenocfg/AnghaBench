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
struct file {struct configfs_buffer* private_data; } ;
struct configfs_buffer {int /*<<< orphan*/  mutex; scalar_t__ page; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct configfs_buffer*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_release(struct inode *inode, struct file *filp)
{
	struct configfs_buffer *buffer = filp->private_data;

	module_put(buffer->owner);
	if (buffer->page)
		free_page((unsigned long)buffer->page);
	mutex_destroy(&buffer->mutex);
	kfree(buffer);
	return 0;
}