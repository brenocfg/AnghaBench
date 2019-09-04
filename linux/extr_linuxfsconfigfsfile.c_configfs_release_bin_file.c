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
struct inode {int dummy; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; struct configfs_buffer* private_data; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct configfs_buffer {int read_in_progress; int write_in_progress; int needs_read_fill; scalar_t__ bin_buffer_size; int /*<<< orphan*/ * bin_buffer; } ;
struct configfs_bin_attribute {scalar_t__ (* write ) (struct config_item*,int /*<<< orphan*/ *,scalar_t__) ;} ;
struct config_item {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int configfs_release (struct inode*,struct file*) ; 
 scalar_t__ stub1 (struct config_item*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct configfs_bin_attribute* to_bin_attr (struct dentry*) ; 
 struct config_item* to_item (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_release_bin_file(struct inode *inode, struct file *filp)
{
	struct configfs_buffer *buffer = filp->private_data;
	struct dentry *dentry = filp->f_path.dentry;
	struct config_item *item = to_item(dentry->d_parent);
	struct configfs_bin_attribute *bin_attr = to_bin_attr(dentry);
	ssize_t len = 0;
	int ret;

	buffer->read_in_progress = false;

	if (buffer->write_in_progress) {
		buffer->write_in_progress = false;

		len = bin_attr->write(item, buffer->bin_buffer,
				buffer->bin_buffer_size);

		/* vfree on NULL is safe */
		vfree(buffer->bin_buffer);
		buffer->bin_buffer = NULL;
		buffer->bin_buffer_size = 0;
		buffer->needs_read_fill = 1;
	}

	ret = configfs_release(inode, filp);
	if (len < 0)
		return len;
	return ret;
}