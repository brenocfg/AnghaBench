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
struct v4l2_requestbuffers {int count; } ;
struct uvc_video_queue {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int vb2_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

int uvcg_alloc_buffers(struct uvc_video_queue *queue,
			      struct v4l2_requestbuffers *rb)
{
	int ret;

	ret = vb2_reqbufs(&queue->queue, rb);

	return ret ? ret : rb->count;
}