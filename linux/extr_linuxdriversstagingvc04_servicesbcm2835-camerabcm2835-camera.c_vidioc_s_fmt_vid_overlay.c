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
struct TYPE_3__ {int /*<<< orphan*/  win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct bm2835_mmal_dev {TYPE_2__** component; int /*<<< orphan*/  overlay; } ;
struct TYPE_4__ {int /*<<< orphan*/ * input; scalar_t__ enabled; } ;

/* Variables and functions */
 size_t COMP_PREVIEW ; 
 int /*<<< orphan*/  set_overlay_params (struct bm2835_mmal_dev*,int /*<<< orphan*/ *) ; 
 struct bm2835_mmal_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vidioc_try_fmt_vid_overlay (struct file*,void*,struct v4l2_format*) ; 

__attribute__((used)) static int vidioc_s_fmt_vid_overlay(struct file *file, void *priv,
				    struct v4l2_format *f)
{
	struct bm2835_mmal_dev *dev = video_drvdata(file);

	vidioc_try_fmt_vid_overlay(file, priv, f);

	dev->overlay = f->fmt.win;
	if (dev->component[COMP_PREVIEW]->enabled) {
		set_overlay_params(dev,
				   &dev->component[COMP_PREVIEW]->input[0]);
	}

	return 0;
}