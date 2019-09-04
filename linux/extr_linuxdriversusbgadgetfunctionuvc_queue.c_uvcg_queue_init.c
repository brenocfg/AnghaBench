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
struct TYPE_2__ {int type; int io_modes; int buf_struct_size; int timestamp_flags; int /*<<< orphan*/ * mem_ops; struct mutex* lock; int /*<<< orphan*/ * ops; struct uvc_video_queue* drv_priv; } ;
struct uvc_video_queue {scalar_t__ flags; int /*<<< orphan*/  irqqueue; int /*<<< orphan*/  irqlock; TYPE_1__ queue; } ;
struct uvc_buffer {int dummy; } ;
struct mutex {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_EOF ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_queue_qops ; 
 int vb2_queue_init (TYPE_1__*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 

int uvcg_queue_init(struct uvc_video_queue *queue, enum v4l2_buf_type type,
		    struct mutex *lock)
{
	int ret;

	queue->queue.type = type;
	queue->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	queue->queue.drv_priv = queue;
	queue->queue.buf_struct_size = sizeof(struct uvc_buffer);
	queue->queue.ops = &uvc_queue_qops;
	queue->queue.lock = lock;
	queue->queue.mem_ops = &vb2_vmalloc_memops;
	queue->queue.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC
				     | V4L2_BUF_FLAG_TSTAMP_SRC_EOF;
	ret = vb2_queue_init(&queue->queue);
	if (ret)
		return ret;

	spin_lock_init(&queue->irqlock);
	INIT_LIST_HEAD(&queue->irqqueue);
	queue->flags = 0;

	return 0;
}