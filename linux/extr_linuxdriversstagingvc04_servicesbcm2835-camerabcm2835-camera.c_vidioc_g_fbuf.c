#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; } ;
struct TYPE_7__ {TYPE_2__ video; } ;
struct vchiq_mmal_port {TYPE_3__ es; } ;
struct TYPE_8__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_framebuffer {int capability; TYPE_4__ fmt; int /*<<< orphan*/  flags; } ;
struct file {int dummy; } ;
struct bm2835_mmal_dev {TYPE_1__** component; } ;
struct TYPE_5__ {struct vchiq_mmal_port* output; } ;

/* Variables and functions */
 size_t CAM_PORT_PREVIEW ; 
 size_t COMP_CAMERA ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int V4L2_FBUF_CAP_EXTERNOVERLAY ; 
 int V4L2_FBUF_CAP_GLOBAL_ALPHA ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_OVERLAY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV420 ; 
 struct bm2835_mmal_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fbuf(struct file *file, void *fh,
			 struct v4l2_framebuffer *a)
{
	/* The video overlay must stay within the framebuffer and can't be
	 * positioned independently.
	 */
	struct bm2835_mmal_dev *dev = video_drvdata(file);
	struct vchiq_mmal_port *preview_port =
		&dev->component[COMP_CAMERA]->output[CAM_PORT_PREVIEW];

	a->capability = V4L2_FBUF_CAP_EXTERNOVERLAY |
			V4L2_FBUF_CAP_GLOBAL_ALPHA;
	a->flags = V4L2_FBUF_FLAG_OVERLAY;
	a->fmt.width = preview_port->es.video.width;
	a->fmt.height = preview_port->es.video.height;
	a->fmt.pixelformat = V4L2_PIX_FMT_YUV420;
	a->fmt.bytesperline = preview_port->es.video.width;
	a->fmt.sizeimage = (preview_port->es.video.width *
			       preview_port->es.video.height * 3) >> 1;
	a->fmt.colorspace = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}