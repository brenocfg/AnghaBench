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
struct TYPE_4__ {unsigned long sizeimage; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_video_device {TYPE_3__ fmt; struct vpfe_device* vpfe_dev; } ;
struct vpfe_fh {struct vpfe_video_device* video; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct vb2_queue {unsigned int num_buffers; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 struct vpfe_fh* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int
vpfe_buffer_queue_setup(struct vb2_queue *vq,
			unsigned int *nbuffers, unsigned int *nplanes,
			unsigned int sizes[], struct device *alloc_devs[])
{
	struct vpfe_fh *fh = vb2_get_drv_priv(vq);
	struct vpfe_video_device *video = fh->video;
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	unsigned long size;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_queue_setup\n");
	size = video->fmt.fmt.pix.sizeimage;

	if (vq->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - vq->num_buffers;

	*nplanes = 1;
	sizes[0] = size;
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
		 "nbuffers=%d, size=%lu\n", *nbuffers, size);
	return 0;
}