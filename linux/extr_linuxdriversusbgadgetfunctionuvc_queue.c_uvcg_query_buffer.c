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
struct v4l2_buffer {int dummy; } ;
struct uvc_video_queue {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int vb2_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

int uvcg_query_buffer(struct uvc_video_queue *queue, struct v4l2_buffer *buf)
{
	return vb2_querybuf(&queue->queue, buf);
}