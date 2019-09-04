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
struct recv_buf {int /*<<< orphan*/  list; } ;
struct __queue {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

sint rtw_enqueue_recvbuf_to_head(struct recv_buf *precvbuf, struct __queue *queue)
{
	spin_lock_bh(&queue->lock);

	list_del_init(&precvbuf->list);
	list_add(&precvbuf->list, get_list_head(queue));

	spin_unlock_bh(&queue->lock);

	return _SUCCESS;
}