#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_mbus_framefmt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct iss_video_fh {struct v4l2_format format; } ;
struct iss_video {scalar_t__ type; int /*<<< orphan*/  mutex; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iss_video_mbus_to_pix (struct iss_video*,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iss_video_pix_to_mbus (int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iss_video_fh* to_iss_video_fh (void*) ; 
 struct iss_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
iss_video_set_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct iss_video_fh *vfh = to_iss_video_fh(fh);
	struct iss_video *video = video_drvdata(file);
	struct v4l2_mbus_framefmt fmt;

	if (format->type != video->type)
		return -EINVAL;

	mutex_lock(&video->mutex);

	/*
	 * Fill the bytesperline and sizeimage fields by converting to media bus
	 * format and back to pixel format.
	 */
	iss_video_pix_to_mbus(&format->fmt.pix, &fmt);
	iss_video_mbus_to_pix(video, &fmt, &format->fmt.pix);

	vfh->format = *format;

	mutex_unlock(&video->mutex);
	return 0;
}