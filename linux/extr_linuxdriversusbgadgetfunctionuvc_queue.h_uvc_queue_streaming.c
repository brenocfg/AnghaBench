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

/* Variables and functions */
 int vb2_is_streaming (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int uvc_queue_streaming(struct uvc_video_queue *queue)
{
	return vb2_is_streaming(&queue->queue);
}