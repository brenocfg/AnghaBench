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
struct tegra_vde_h264_frame {int frame_num; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int tegra_vde_validate_frame(struct device *dev,
				    struct tegra_vde_h264_frame *frame)
{
	if (frame->frame_num > 0x7FFFFF) {
		dev_err(dev, "Bad frame_num %u\n", frame->frame_num);
		return -EINVAL;
	}

	return 0;
}