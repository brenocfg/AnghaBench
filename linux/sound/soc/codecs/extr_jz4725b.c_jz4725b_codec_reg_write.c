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
struct jz_icdc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ICDC_RGADW_OFFSET ; 
 unsigned int ICDC_RGADW_RGADDR_OFFSET ; 
 unsigned int ICDC_RGADW_RGWR ; 
 int jz4725b_codec_io_wait (struct jz_icdc*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int jz4725b_codec_reg_write(void *context, unsigned int reg,
				   unsigned int val)
{
	struct jz_icdc *icdc = context;
	int ret;

	ret = jz4725b_codec_io_wait(icdc);
	if (ret)
		return ret;

	writel(ICDC_RGADW_RGWR | (reg << ICDC_RGADW_RGADDR_OFFSET) | val,
			icdc->base + ICDC_RGADW_OFFSET);

	ret = jz4725b_codec_io_wait(icdc);
	if (ret)
		return ret;

	return 0;
}