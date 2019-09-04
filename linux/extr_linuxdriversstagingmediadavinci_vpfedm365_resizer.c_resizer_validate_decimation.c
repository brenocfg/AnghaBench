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
struct device {int dummy; } ;
typedef  enum ipipeif_decimation { ____Placeholder_ipipeif_decimation } ipipeif_decimation ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char IPIPEIF_RSZ_MAX ; 
 unsigned char IPIPEIF_RSZ_MIN ; 
 int VPFE_IPIPE_MAX_INPUT_WIDTH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 

__attribute__((used)) static int
resizer_validate_decimation(struct device *dev, enum ipipeif_decimation dec_en,
			    unsigned char rsz, unsigned char frame_div_mode_en,
			    int width)
{
	if (dec_en && frame_div_mode_en) {
		dev_err(dev,
		 "dec_en & frame_div_mode_en can not enabled simultaneously\n");
		return -EINVAL;
	}

	if (frame_div_mode_en) {
		dev_err(dev, "frame_div_mode mode not supported\n");
		return -EINVAL;
	}

	if (!dec_en)
		return 0;

	if (width <= VPFE_IPIPE_MAX_INPUT_WIDTH) {
		dev_err(dev,
			"image width to be more than %d for decimation\n",
			VPFE_IPIPE_MAX_INPUT_WIDTH);
		return -EINVAL;
	}

	if (rsz < IPIPEIF_RSZ_MIN || rsz > IPIPEIF_RSZ_MAX) {
		dev_err(dev, "rsz range is %d to %d\n",
			IPIPEIF_RSZ_MIN, IPIPEIF_RSZ_MAX);
		return -EINVAL;
	}

	return 0;
}