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
typedef  scalar_t__ const u64 ;
struct ni_gpct_device {int variant; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int GI_660X_ALT_SYNC ; 
 unsigned int GI_CNT_MODE_MASK ; 
#define  GI_CNT_MODE_QUADX1 134 
#define  GI_CNT_MODE_QUADX2 133 
#define  GI_CNT_MODE_QUADX4 132 
#define  GI_CNT_MODE_SYNC_SRC 131 
 unsigned int GI_M_ALT_SYNC ; 
 unsigned int NITIO_CNT_MODE_REG (unsigned int) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_tio_clock_period_ps (struct ni_gpct*,unsigned int,scalar_t__ const*) ; 
 int ni_tio_generic_clock_src_select (struct ni_gpct*,unsigned int*) ; 
 unsigned int ni_tio_get_soft_copy (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void ni_tio_set_sync_mode(struct ni_gpct *counter)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	static const u64 min_normal_sync_period_ps = 25000;
	unsigned int mask = 0;
	unsigned int bits = 0;
	unsigned int reg;
	unsigned int mode;
	unsigned int clk_src = 0;
	u64 ps = 0;
	int ret;
	bool force_alt_sync;

	/* only m series and 660x variants have counting mode registers */
	switch (counter_dev->variant) {
	case ni_gpct_variant_e_series:
	default:
		return;
	case ni_gpct_variant_m_series:
		mask = GI_M_ALT_SYNC;
		break;
	case ni_gpct_variant_660x:
		mask = GI_660X_ALT_SYNC;
		break;
	}

	reg = NITIO_CNT_MODE_REG(cidx);
	mode = ni_tio_get_soft_copy(counter, reg);
	switch (mode & GI_CNT_MODE_MASK) {
	case GI_CNT_MODE_QUADX1:
	case GI_CNT_MODE_QUADX2:
	case GI_CNT_MODE_QUADX4:
	case GI_CNT_MODE_SYNC_SRC:
		force_alt_sync = true;
		break;
	default:
		force_alt_sync = false;
		break;
	}

	ret = ni_tio_generic_clock_src_select(counter, &clk_src);
	if (ret)
		return;
	ret = ni_tio_clock_period_ps(counter, clk_src, &ps);
	if (ret)
		return;
	/*
	 * It's not clear what we should do if clock_period is unknown, so we
	 * are not using the alt sync bit in that case.
	 */
	if (force_alt_sync || (ps && ps < min_normal_sync_period_ps))
		bits = mask;

	ni_tio_set_bits(counter, reg, mask, bits);
}