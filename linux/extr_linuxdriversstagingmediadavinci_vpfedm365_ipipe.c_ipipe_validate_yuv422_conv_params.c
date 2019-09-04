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
struct vpfe_ipipe_yuv422_conv {int en_chrom_lpf; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
ipipe_validate_yuv422_conv_params(struct vpfe_ipipe_yuv422_conv *yuv422_conv)
{
	if (yuv422_conv->en_chrom_lpf > 1)
		return -EINVAL;

	return 0;
}