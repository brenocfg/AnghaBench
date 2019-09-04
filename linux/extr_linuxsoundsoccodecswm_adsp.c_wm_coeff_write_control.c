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
struct wm_coeff_ctl {struct wm_adsp* dsp; } ;
struct wm_adsp {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  adsp_dbg (struct wm_adsp*,char*,size_t,unsigned int) ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,size_t,unsigned int,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void const*,size_t,int) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,unsigned int,void*,size_t) ; 
 int wm_coeff_base_reg (struct wm_coeff_ctl*,unsigned int*) ; 

__attribute__((used)) static int wm_coeff_write_control(struct wm_coeff_ctl *ctl,
				  const void *buf, size_t len)
{
	struct wm_adsp *dsp = ctl->dsp;
	void *scratch;
	int ret;
	unsigned int reg;

	ret = wm_coeff_base_reg(ctl, &reg);
	if (ret)
		return ret;

	scratch = kmemdup(buf, len, GFP_KERNEL | GFP_DMA);
	if (!scratch)
		return -ENOMEM;

	ret = regmap_raw_write(dsp->regmap, reg, scratch,
			       len);
	if (ret) {
		adsp_err(dsp, "Failed to write %zu bytes to %x: %d\n",
			 len, reg, ret);
		kfree(scratch);
		return ret;
	}
	adsp_dbg(dsp, "Wrote %zu bytes to %x\n", len, reg);

	kfree(scratch);

	return 0;
}