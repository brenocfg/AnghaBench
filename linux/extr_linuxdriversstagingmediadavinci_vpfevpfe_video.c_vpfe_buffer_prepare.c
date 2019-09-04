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
struct TYPE_4__ {int /*<<< orphan*/  sizeimage; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_video_device {TYPE_3__ fmt; struct vpfe_device* vpfe_dev; } ;
struct vpfe_fh {struct vpfe_video_device* video; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct vb2_buffer {scalar_t__ state; int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (unsigned long,int) ; 
 int EINVAL ; 
 scalar_t__ VB2_BUF_STATE_ACTIVE ; 
 scalar_t__ VB2_BUF_STATE_PREPARED ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 unsigned long vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct vpfe_fh* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_buffer_prepare(struct vb2_buffer *vb)
{
	struct vpfe_fh *fh = vb2_get_drv_priv(vb->vb2_queue);
	struct vpfe_video_device *video = fh->video;
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	unsigned long addr;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_prepare\n");

	if (vb->state != VB2_BUF_STATE_ACTIVE &&
	    vb->state != VB2_BUF_STATE_PREPARED)
		return 0;

	/* Initialize buffer */
	vb2_set_plane_payload(vb, 0, video->fmt.fmt.pix.sizeimage);
	if (vb2_plane_vaddr(vb, 0) &&
	    vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		return -EINVAL;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	/* Make sure user addresses are aligned to 32 bytes */
	if (!ALIGN(addr, 32))
		return -EINVAL;

	return 0;
}