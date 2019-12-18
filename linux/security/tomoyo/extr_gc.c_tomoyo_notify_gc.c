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
struct tomoyo_io_buffer {int users; struct tomoyo_io_buffer* write_buf; struct tomoyo_io_buffer* read_buf; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tomoyo_io_buffer*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_gc_thread ; 
 int /*<<< orphan*/  tomoyo_io_buffer_list ; 
 int /*<<< orphan*/  tomoyo_io_buffer_list_lock ; 

void tomoyo_notify_gc(struct tomoyo_io_buffer *head, const bool is_register)
{
	bool is_write = false;

	spin_lock(&tomoyo_io_buffer_list_lock);
	if (is_register) {
		head->users = 1;
		list_add(&head->list, &tomoyo_io_buffer_list);
	} else {
		is_write = head->write_buf != NULL;
		if (!--head->users) {
			list_del(&head->list);
			kfree(head->read_buf);
			kfree(head->write_buf);
			kfree(head);
		}
	}
	spin_unlock(&tomoyo_io_buffer_list_lock);
	if (is_write)
		kthread_run(tomoyo_gc_thread, NULL, "GC for TOMOYO");
}