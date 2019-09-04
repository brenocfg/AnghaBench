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
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 scalar_t__ MEDIA_BUS_FMT_UV8_1X8 ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 
 scalar_t__ MEDIA_BUS_FMT_YDYUYDYV8_1X16 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  resizer_calculate_line_length (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static inline int
resizer_validate_output_image_format(struct device *dev,
				     struct v4l2_mbus_framefmt *format,
				     int *in_line_len, int *in_line_len_c)
{
	if (format->code != MEDIA_BUS_FMT_UYVY8_2X8 &&
	    format->code != MEDIA_BUS_FMT_Y8_1X8 &&
	    format->code != MEDIA_BUS_FMT_UV8_1X8 &&
	    format->code != MEDIA_BUS_FMT_YDYUYDYV8_1X16 &&
	    format->code != MEDIA_BUS_FMT_SGRBG12_1X12) {
		dev_err(dev, "Invalid Mbus format, %d\n", format->code);
		return -EINVAL;
	}
	if (!format->width || !format->height) {
		dev_err(dev, "invalid width or height\n");
		return -EINVAL;
	}
	resizer_calculate_line_length(format->code, format->width,
		format->height, in_line_len, in_line_len_c);
	return 0;
}