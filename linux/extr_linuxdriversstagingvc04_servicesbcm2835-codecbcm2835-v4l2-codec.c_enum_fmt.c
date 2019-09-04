#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  flags; int /*<<< orphan*/  pixelformat; } ;
struct bcm2835_codec_fmt_list {size_t num_entries; struct bcm2835_codec_fmt* list; } ;
struct bcm2835_codec_fmt {int /*<<< orphan*/  flags; int /*<<< orphan*/  fourcc; } ;
struct bcm2835_codec_ctx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bcm2835_codec_fmt_list* get_format_list (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int enum_fmt(struct v4l2_fmtdesc *f, struct bcm2835_codec_ctx *ctx,
		    bool capture)
{
	struct bcm2835_codec_fmt *fmt;
	struct bcm2835_codec_fmt_list *fmts =
					get_format_list(ctx->dev, capture);

	if (f->index < fmts->num_entries) {
		/* Format found */
		fmt = &fmts->list[f->index];
		f->pixelformat = fmt->fourcc;
		f->flags = fmt->flags;
		return 0;
	}

	/* Format not found */
	return -EINVAL;
}