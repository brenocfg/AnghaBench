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
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  field; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  sizeimage; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct bcm2835_codec_fmt {int /*<<< orphan*/  flags; } ;
struct bcm2835_codec_ctx {TYPE_1__* dev; } ;
struct TYPE_4__ {scalar_t__ role; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 scalar_t__ ISP ; 
 scalar_t__ MAX_H ; 
 scalar_t__ MAX_W ; 
 scalar_t__ MIN_H ; 
 scalar_t__ MIN_W ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int V4L2_FMT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  get_bytesperline (scalar_t__,struct bcm2835_codec_fmt*) ; 
 int /*<<< orphan*/  get_sizeimage (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct bcm2835_codec_fmt*) ; 

__attribute__((used)) static int vidioc_try_fmt(struct bcm2835_codec_ctx *ctx, struct v4l2_format *f,
			  struct bcm2835_codec_fmt *fmt)
{
	/*
	 * The V4L2 specification requires the driver to correct the format
	 * struct if any of the dimensions is unsupported
	 */
	if (f->fmt.pix.width > MAX_W)
		f->fmt.pix.width = MAX_W;
	if (f->fmt.pix.height > MAX_H)
		f->fmt.pix.height = MAX_H;

	if (!fmt->flags & V4L2_FMT_FLAG_COMPRESSED) {
		/* Only clip min w/h on capture. Treat 0x0 as unknown. */
		if (f->fmt.pix.width < MIN_W)
			f->fmt.pix.width = MIN_W;
		if (f->fmt.pix.height < MIN_H)
			f->fmt.pix.height = MIN_H;

		/*
		 * For codecs the buffer must have a vertical alignment of 16
		 * lines.
		 * The selection will reflect any cropping rectangle when only
		 * some of the pixels are active.
		 */
		if (ctx->dev->role != ISP)
			f->fmt.pix.height = ALIGN(f->fmt.pix.height, 16);
	}
	f->fmt.pix.bytesperline = get_bytesperline(f->fmt.pix.width,
						   fmt);
	f->fmt.pix.sizeimage = get_sizeimage(f->fmt.pix.bytesperline,
					     f->fmt.pix.width,
					     f->fmt.pix.height,
					     fmt);

	f->fmt.pix.field = V4L2_FIELD_NONE;

	return 0;
}