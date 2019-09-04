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
struct bcm2835_codec_fmt {int flags; int size_multiplier_x2; } ;

/* Variables and functions */
 unsigned int DEF_COMP_BUF_SIZE_720P_OR_LESS ; 
 unsigned int DEF_COMP_BUF_SIZE_GREATER_720P ; 
 int V4L2_FMT_FLAG_COMPRESSED ; 

__attribute__((used)) static inline unsigned int get_sizeimage(int bpl, int width, int height,
					 struct bcm2835_codec_fmt *fmt)
{
	if (fmt->flags & V4L2_FMT_FLAG_COMPRESSED) {
		if (width * height > 1280 * 720)
			return DEF_COMP_BUF_SIZE_GREATER_720P;
		else
			return DEF_COMP_BUF_SIZE_720P_OR_LESS;
	} else {
		return (bpl * height * fmt->size_multiplier_x2) >> 1;
	}
}