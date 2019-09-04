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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 scalar_t__ MEDIA_BUS_FMT_UV8_1X8 ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 scalar_t__ MEDIA_BUS_FMT_Y8_1X8 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  resizer_calculate_line_length (scalar_t__,int,int,int*,int*) ; 

__attribute__((used)) static inline int
resizer_validate_input_image_format(struct device *dev,
				    u32 pix,
				    int width, int height, int *line_len)
{
	int val;

	if (pix != MEDIA_BUS_FMT_UYVY8_2X8 &&
	    pix != MEDIA_BUS_FMT_Y8_1X8 &&
	    pix != MEDIA_BUS_FMT_UV8_1X8 &&
	    pix != MEDIA_BUS_FMT_SGRBG12_1X12) {
		dev_err(dev,
		"resizer validate output: pix format not supported, %d\n", pix);
		return -EINVAL;
	}

	if (!width || !height) {
		dev_err(dev,
			"resizer validate input: invalid width or height\n");
		return -EINVAL;
	}

	if (pix == MEDIA_BUS_FMT_UV8_1X8)
		resizer_calculate_line_length(pix, width,
					      height, &val, line_len);
	else
		resizer_calculate_line_length(pix, width,
					      height, line_len, &val);

	return 0;
}