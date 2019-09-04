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
struct n_hdlc_buf_list {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct n_hdlc_buf {int /*<<< orphan*/  list_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void n_hdlc_buf_put(struct n_hdlc_buf_list *buf_list,
			   struct n_hdlc_buf *buf)
{
	unsigned long flags;

	spin_lock_irqsave(&buf_list->spinlock, flags);

	list_add_tail(&buf->list_item, &buf_list->list);
	buf_list->count++;

	spin_unlock_irqrestore(&buf_list->spinlock, flags);
}