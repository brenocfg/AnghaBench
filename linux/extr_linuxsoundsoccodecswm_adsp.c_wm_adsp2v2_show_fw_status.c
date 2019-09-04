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
 scalar_t__ ADSP2V2_SCRATCH0_1 ; 
 scalar_t__ ADSP2V2_SCRATCH2_3 ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static void wm_adsp2v2_show_fw_status(struct wm_adsp *dsp)
{
	unsigned int scratch[2];
	int ret;

	ret = regmap_read(dsp->regmap, dsp->base + ADSP2V2_SCRATCH0_1,
			  &scratch[0]);
	if (ret) {
		adsp_err(dsp, "Failed to read SCRATCH0_1: %d\n", ret);
		return;
	}

	ret = regmap_read(dsp->regmap, dsp->base + ADSP2V2_SCRATCH2_3,
			  &scratch[1]);
	if (ret) {
		adsp_err(dsp, "Failed to read SCRATCH2_3: %d\n", ret);
		return;
	}

	adsp_dbg(dsp, "FW SCRATCH 0:0x%x 1:0x%x 2:0x%x 3:0x%x\n",
		 scratch[0] & 0xFFFF,
		 scratch[0] >> 16,
		 scratch[1] & 0xFFFF,
		 scratch[1] >> 16);
}