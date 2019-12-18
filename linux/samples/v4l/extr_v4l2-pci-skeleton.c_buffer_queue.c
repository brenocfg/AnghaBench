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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct skeleton {int /*<<< orphan*/  qlock; int /*<<< orphan*/  buf_list; } ;
struct skel_buffer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct skel_buffer* to_skel_buffer (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct skeleton* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_queue(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct skeleton *skel = vb2_get_drv_priv(vb->vb2_queue);
	struct skel_buffer *buf = to_skel_buffer(vbuf);
	unsigned long flags;

	spin_lock_irqsave(&skel->qlock, flags);
	list_add_tail(&buf->list, &skel->buf_list);

	/* TODO: Update any DMA pointers if necessary */

	spin_unlock_irqrestore(&skel->qlock, flags);
}