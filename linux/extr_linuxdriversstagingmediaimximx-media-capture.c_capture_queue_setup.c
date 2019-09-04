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
struct vb2_queue {scalar_t__ type; unsigned int num_buffers; } ;
struct v4l2_pix_format {unsigned int sizeimage; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct capture_priv {TYPE_3__ vdev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int VID_MEM_LIMIT ; 
 int /*<<< orphan*/  __u32 ; 
 unsigned int min_t (int /*<<< orphan*/ ,int,unsigned int) ; 
 struct capture_priv* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int capture_queue_setup(struct vb2_queue *vq,
			       unsigned int *nbuffers,
			       unsigned int *nplanes,
			       unsigned int sizes[],
			       struct device *alloc_devs[])
{
	struct capture_priv *priv = vb2_get_drv_priv(vq);
	struct v4l2_pix_format *pix = &priv->vdev.fmt.fmt.pix;
	unsigned int count = *nbuffers;

	if (vq->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if (*nplanes) {
		if (*nplanes != 1 || sizes[0] < pix->sizeimage)
			return -EINVAL;
		count += vq->num_buffers;
	}

	count = min_t(__u32, VID_MEM_LIMIT / pix->sizeimage, count);

	if (*nplanes)
		*nbuffers = (count < vq->num_buffers) ? 0 :
			count - vq->num_buffers;
	else
		*nbuffers = count;

	*nplanes = 1;
	sizes[0] = pix->sizeimage;

	return 0;
}