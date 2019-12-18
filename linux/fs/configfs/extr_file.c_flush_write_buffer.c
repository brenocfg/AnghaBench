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
struct configfs_buffer {int /*<<< orphan*/  page; int /*<<< orphan*/  item; TYPE_1__* attr; } ;
struct TYPE_2__ {int (* store ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct configfs_fragment* to_frag (struct file*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
flush_write_buffer(struct file *file, struct configfs_buffer *buffer, size_t count)
{
	struct configfs_fragment *frag = to_frag(file);
	int res = -ENOENT;

	down_read(&frag->frag_sem);
	if (!frag->frag_dead)
		res = buffer->attr->store(buffer->item, buffer->page, count);
	up_read(&frag->frag_sem);
	return res;
}