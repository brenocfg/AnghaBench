#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; scalar_t__ priv; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_3__ {int width; int height; scalar_t__ interlaced; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;
struct skeleton {scalar_t__ input; int std; TYPE_2__ timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_ALTERNATE ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 int V4L2_STD_525_60 ; 

__attribute__((used)) static void skeleton_fill_pix_format(struct skeleton *skel,
				     struct v4l2_pix_format *pix)
{
	pix->pixelformat = V4L2_PIX_FMT_YUYV;
	if (skel->input == 0) {
		/* S-Video input */
		pix->width = 720;
		pix->height = (skel->std & V4L2_STD_525_60) ? 480 : 576;
		pix->field = V4L2_FIELD_INTERLACED;
		pix->colorspace = V4L2_COLORSPACE_SMPTE170M;
	} else {
		/* HDMI input */
		pix->width = skel->timings.bt.width;
		pix->height = skel->timings.bt.height;
		if (skel->timings.bt.interlaced) {
			pix->field = V4L2_FIELD_ALTERNATE;
			pix->height /= 2;
		} else {
			pix->field = V4L2_FIELD_NONE;
		}
		pix->colorspace = V4L2_COLORSPACE_REC709;
	}

	/*
	 * The YUYV format is four bytes for every two pixels, so bytesperline
	 * is width * 2.
	 */
	pix->bytesperline = pix->width * 2;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->priv = 0;
}