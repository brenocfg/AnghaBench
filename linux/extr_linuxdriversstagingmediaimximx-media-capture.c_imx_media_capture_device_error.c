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
struct vb2_queue {int dummy; } ;
struct imx_media_video_dev {int dummy; } ;
struct capture_priv {int /*<<< orphan*/  q_lock; struct vb2_queue q; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct capture_priv* to_capture_priv (struct imx_media_video_dev*) ; 
 int /*<<< orphan*/  vb2_is_streaming (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_queue_error (struct vb2_queue*) ; 

void imx_media_capture_device_error(struct imx_media_video_dev *vdev)
{
	struct capture_priv *priv = to_capture_priv(vdev);
	struct vb2_queue *vq = &priv->q;
	unsigned long flags;

	if (!vb2_is_streaming(vq))
		return;

	spin_lock_irqsave(&priv->q_lock, flags);
	vb2_queue_error(vq);
	spin_unlock_irqrestore(&priv->q_lock, flags);
}