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
struct wm_adsp {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ADSP2_RAM_RDY ; 
 scalar_t__ ADSP2_STATUS1 ; 
 int EBUSY ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,int) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wm_adsp2v2_enable_core(struct wm_adsp *dsp)
{
	unsigned int val;
	int ret, count;

	/* Wait for the RAM to start, should be near instantaneous */
	for (count = 0; count < 10; ++count) {
		ret = regmap_read(dsp->regmap, dsp->base + ADSP2_STATUS1, &val);
		if (ret != 0)
			return ret;

		if (val & ADSP2_RAM_RDY)
			break;

		usleep_range(250, 500);
	}

	if (!(val & ADSP2_RAM_RDY)) {
		adsp_err(dsp, "Failed to start DSP RAM\n");
		return -EBUSY;
	}

	adsp_dbg(dsp, "RAM ready after %d polls\n", count);

	return 0;
}