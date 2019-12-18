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
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,unsigned int,int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static void wm_adsp_read_fw_status(struct wm_adsp *dsp,
				   int noffs, unsigned int *offs)
{
	unsigned int i;
	int ret;

	for (i = 0; i < noffs; ++i) {
		ret = regmap_read(dsp->regmap, dsp->base + offs[i], &offs[i]);
		if (ret) {
			adsp_err(dsp, "Failed to read SCRATCH%u: %d\n", i, ret);
			return;
		}
	}
}