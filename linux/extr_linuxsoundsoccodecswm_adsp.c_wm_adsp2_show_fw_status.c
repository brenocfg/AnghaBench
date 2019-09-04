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
struct wm_adsp {unsigned int base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ADSP2_SCRATCH0 ; 
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,unsigned int,int) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static void wm_adsp2_show_fw_status(struct wm_adsp *dsp)
{
	unsigned int scratch[4];
	unsigned int addr = dsp->base + ADSP2_SCRATCH0;
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(scratch); ++i) {
		ret = regmap_read(dsp->regmap, addr + i, &scratch[i]);
		if (ret) {
			adsp_err(dsp, "Failed to read SCRATCH%u: %d\n", i, ret);
			return;
		}
	}

	adsp_dbg(dsp, "FW SCRATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		 scratch[0], scratch[1], scratch[2], scratch[3]);
}