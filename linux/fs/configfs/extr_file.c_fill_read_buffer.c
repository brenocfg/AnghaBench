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
struct file {int dummy; } ;
struct configfs_fragment {int /*<<< orphan*/  frag_sem; int /*<<< orphan*/  frag_dead; } ;
struct configfs_buffer {char* page; scalar_t__ count; scalar_t__ needs_read_fill; int /*<<< orphan*/  item; TYPE_1__* attr; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ (* show ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SIMPLE_ATTR_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*) ; 
 struct configfs_fragment* to_frag (struct file*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_read_buffer(struct file *file, struct configfs_buffer *buffer)
{
	struct configfs_fragment *frag = to_frag(file);
	ssize_t count = -ENOENT;

	if (!buffer->page)
		buffer->page = (char *) get_zeroed_page(GFP_KERNEL);
	if (!buffer->page)
		return -ENOMEM;

	down_read(&frag->frag_sem);
	if (!frag->frag_dead)
		count = buffer->attr->show(buffer->item, buffer->page);
	up_read(&frag->frag_sem);

	if (count < 0)
		return count;
	if (WARN_ON_ONCE(count > (ssize_t)SIMPLE_ATTR_SIZE))
		return -EIO;
	buffer->needs_read_fill = 0;
	buffer->count = count;
	return 0;
}