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
struct file {struct configfs_buffer* private_data; } ;
struct configfs_fragment {int /*<<< orphan*/  frag_sem; int /*<<< orphan*/  frag_dead; } ;
struct configfs_buffer {int read_in_progress; int write_in_progress; int needs_read_fill; scalar_t__ bin_buffer_size; int /*<<< orphan*/ * bin_buffer; int /*<<< orphan*/  item; TYPE_1__* bin_attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_release (struct inode*,struct file*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct configfs_fragment* to_frag (struct file*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_release_bin_file(struct inode *inode, struct file *file)
{
	struct configfs_buffer *buffer = file->private_data;

	buffer->read_in_progress = false;

	if (buffer->write_in_progress) {
		struct configfs_fragment *frag = to_frag(file);
		buffer->write_in_progress = false;

		down_read(&frag->frag_sem);
		if (!frag->frag_dead) {
			/* result of ->release() is ignored */
			buffer->bin_attr->write(buffer->item,
					buffer->bin_buffer,
					buffer->bin_buffer_size);
		}
		up_read(&frag->frag_sem);
		/* vfree on NULL is safe */
		vfree(buffer->bin_buffer);
		buffer->bin_buffer = NULL;
		buffer->bin_buffer_size = 0;
		buffer->needs_read_fill = 1;
	}

	configfs_release(inode, file);
	return 0;
}