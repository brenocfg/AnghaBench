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
struct uvc_video_queue {int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  vb2_poll (int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *) ; 

__poll_t uvcg_queue_poll(struct uvc_video_queue *queue, struct file *file,
			     poll_table *wait)
{
	return vb2_poll(&queue->queue, file, wait);
}