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
struct v4l2_pix_format {scalar_t__ bytesperline; scalar_t__ pixelformat; scalar_t__ height; scalar_t__ width; scalar_t__ sizeimage; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct TYPE_4__ {scalar_t__ pixelformat; scalar_t__ height; scalar_t__ width; scalar_t__ bytesperline; scalar_t__ sizeimage; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct iss_video_fh {TYPE_3__ format; } ;
struct iss_video {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __iss_video_get_format (struct iss_video*,struct v4l2_mbus_framefmt*) ; 
 int iss_video_mbus_to_pix (struct iss_video*,struct v4l2_mbus_framefmt*,struct v4l2_pix_format*) ; 

__attribute__((used)) static int
iss_video_check_format(struct iss_video *video, struct iss_video_fh *vfh)
{
	struct v4l2_mbus_framefmt format;
	struct v4l2_pix_format pixfmt;
	int ret;

	ret = __iss_video_get_format(video, &format);
	if (ret < 0)
		return ret;

	pixfmt.bytesperline = 0;
	ret = iss_video_mbus_to_pix(video, &format, &pixfmt);

	if (vfh->format.fmt.pix.pixelformat != pixfmt.pixelformat ||
	    vfh->format.fmt.pix.height != pixfmt.height ||
	    vfh->format.fmt.pix.width != pixfmt.width ||
	    vfh->format.fmt.pix.bytesperline != pixfmt.bytesperline ||
	    vfh->format.fmt.pix.sizeimage != pixfmt.sizeimage)
		return -EINVAL;

	return ret;
}