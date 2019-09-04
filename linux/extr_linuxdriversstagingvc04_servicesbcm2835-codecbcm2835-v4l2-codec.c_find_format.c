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
struct TYPE_3__ {scalar_t__ pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct bcm2835_codec_fmt_list {unsigned int num_entries; struct bcm2835_codec_fmt* list; } ;
struct bcm2835_codec_fmt {scalar_t__ fourcc; } ;
struct bcm2835_codec_dev {struct bcm2835_codec_fmt_list* supported_fmts; } ;

/* Variables and functions */

__attribute__((used)) static struct bcm2835_codec_fmt *find_format(struct v4l2_format *f,
					     struct bcm2835_codec_dev *dev,
					     bool capture)
{
	struct bcm2835_codec_fmt *fmt;
	unsigned int k;
	struct bcm2835_codec_fmt_list *fmts =
					&dev->supported_fmts[capture ? 1 : 0];

	for (k = 0; k < fmts->num_entries; k++) {
		fmt = &fmts->list[k];
		if (fmt->fourcc == f->fmt.pix.pixelformat)
			break;
	}
	if (k == fmts->num_entries)
		return NULL;

	return &fmts->list[k];
}