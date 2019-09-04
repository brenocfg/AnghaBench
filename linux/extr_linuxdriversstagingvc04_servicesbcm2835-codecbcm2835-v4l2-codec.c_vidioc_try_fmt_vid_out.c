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
struct TYPE_5__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct bcm2835_codec_fmt {int dummy; } ;
struct bcm2835_codec_ctx {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 struct bcm2835_codec_ctx* file2ctx (struct file*) ; 
 struct bcm2835_codec_fmt* find_format (struct v4l2_format*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* get_default_format (int /*<<< orphan*/ ,int) ; 
 int vidioc_try_fmt (struct bcm2835_codec_ctx*,struct v4l2_format*,struct bcm2835_codec_fmt*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_out(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct bcm2835_codec_fmt *fmt;
	struct bcm2835_codec_ctx *ctx = file2ctx(file);

	fmt = find_format(f, ctx->dev, false);
	if (!fmt) {
		f->fmt.pix.pixelformat = get_default_format(ctx->dev,
							    false)->fourcc;
		fmt = find_format(f, ctx->dev, false);
	}

	if (!f->fmt.pix.colorspace)
		f->fmt.pix.colorspace = ctx->colorspace;

	return vidioc_try_fmt(ctx, f, fmt);
}