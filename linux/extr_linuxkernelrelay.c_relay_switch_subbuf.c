#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rchan_buf {int offset; int prev_padding; size_t subbufs_produced; int* padding; TYPE_2__* chan; void* data; void* start; int /*<<< orphan*/  wakeup_work; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  early_bytes; scalar_t__ dentry; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_size; } ;
struct TYPE_5__ {size_t subbuf_size; size_t n_subbufs; size_t last_toobig; TYPE_1__* cb; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* subbuf_start ) (struct rchan_buf*,void*,void*,int) ;} ;

/* Variables and functions */
 TYPE_3__* d_inode (scalar_t__) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stub1 (struct rchan_buf*,void*,void*,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

size_t relay_switch_subbuf(struct rchan_buf *buf, size_t length)
{
	void *old, *new;
	size_t old_subbuf, new_subbuf;

	if (unlikely(length > buf->chan->subbuf_size))
		goto toobig;

	if (buf->offset != buf->chan->subbuf_size + 1) {
		buf->prev_padding = buf->chan->subbuf_size - buf->offset;
		old_subbuf = buf->subbufs_produced % buf->chan->n_subbufs;
		buf->padding[old_subbuf] = buf->prev_padding;
		buf->subbufs_produced++;
		if (buf->dentry)
			d_inode(buf->dentry)->i_size +=
				buf->chan->subbuf_size -
				buf->padding[old_subbuf];
		else
			buf->early_bytes += buf->chan->subbuf_size -
					    buf->padding[old_subbuf];
		smp_mb();
		if (waitqueue_active(&buf->read_wait)) {
			/*
			 * Calling wake_up_interruptible() from here
			 * will deadlock if we happen to be logging
			 * from the scheduler (trying to re-grab
			 * rq->lock), so defer it.
			 */
			irq_work_queue(&buf->wakeup_work);
		}
	}

	old = buf->data;
	new_subbuf = buf->subbufs_produced % buf->chan->n_subbufs;
	new = buf->start + new_subbuf * buf->chan->subbuf_size;
	buf->offset = 0;
	if (!buf->chan->cb->subbuf_start(buf, new, old, buf->prev_padding)) {
		buf->offset = buf->chan->subbuf_size + 1;
		return 0;
	}
	buf->data = new;
	buf->padding[new_subbuf] = 0;

	if (unlikely(length + buf->offset > buf->chan->subbuf_size))
		goto toobig;

	return length;

toobig:
	buf->chan->last_toobig = length;
	return 0;
}