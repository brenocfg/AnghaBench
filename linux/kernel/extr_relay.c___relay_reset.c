#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rchan_buf {int /*<<< orphan*/  data; TYPE_2__* chan; scalar_t__* padding; scalar_t__ offset; int /*<<< orphan*/  start; scalar_t__ finalized; scalar_t__ bytes_consumed; scalar_t__ subbufs_consumed; scalar_t__ subbufs_produced; int /*<<< orphan*/  wakeup_work; int /*<<< orphan*/  kref; int /*<<< orphan*/  read_wait; } ;
struct TYPE_4__ {size_t n_subbufs; TYPE_1__* cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* subbuf_start ) (struct rchan_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rchan_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_readers ; 

__attribute__((used)) static void __relay_reset(struct rchan_buf *buf, unsigned int init)
{
	size_t i;

	if (init) {
		init_waitqueue_head(&buf->read_wait);
		kref_init(&buf->kref);
		init_irq_work(&buf->wakeup_work, wakeup_readers);
	} else {
		irq_work_sync(&buf->wakeup_work);
	}

	buf->subbufs_produced = 0;
	buf->subbufs_consumed = 0;
	buf->bytes_consumed = 0;
	buf->finalized = 0;
	buf->data = buf->start;
	buf->offset = 0;

	for (i = 0; i < buf->chan->n_subbufs; i++)
		buf->padding[i] = 0;

	buf->chan->cb->subbuf_start(buf, buf->data, NULL, 0);
}