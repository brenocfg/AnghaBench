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
struct wm_adsp {scalar_t__ base; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ADSP2_BUS_ERR_ADDR ; 
 unsigned int ADSP2_BUS_ERR_ADDR_MASK ; 
 int /*<<< orphan*/  ADSP2_CTRL_ERR_EINT ; 
 scalar_t__ ADSP2_LOCK_REGION_CTRL ; 
 unsigned int ADSP2_PMEM_ERR_ADDR_MASK ; 
 unsigned int ADSP2_PMEM_ERR_ADDR_SHIFT ; 
 scalar_t__ ADSP2_PMEM_ERR_ADDR_XMEM_ERR_ADDR ; 
 unsigned int ADSP2_REGION_LOCK_ERR_MASK ; 
 unsigned int ADSP2_SLAVE_ERR_MASK ; 
 unsigned int ADSP2_WDT_TIMEOUT_STS_MASK ; 
 unsigned int ADSP2_XMEM_ERR_ADDR_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  adsp_err (struct wm_adsp*,char*,...) ; 
 int regmap_read (struct regmap*,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm_adsp_stop_watchdog (struct wm_adsp*) ; 

irqreturn_t wm_adsp2_bus_error(struct wm_adsp *dsp)
{
	unsigned int val;
	struct regmap *regmap = dsp->regmap;
	int ret = 0;

	ret = regmap_read(regmap, dsp->base + ADSP2_LOCK_REGION_CTRL, &val);
	if (ret) {
		adsp_err(dsp,
			"Failed to read Region Lock Ctrl register: %d\n", ret);
		return IRQ_HANDLED;
	}

	if (val & ADSP2_WDT_TIMEOUT_STS_MASK) {
		adsp_err(dsp, "watchdog timeout error\n");
		wm_adsp_stop_watchdog(dsp);
	}

	if (val & (ADSP2_SLAVE_ERR_MASK | ADSP2_REGION_LOCK_ERR_MASK)) {
		if (val & ADSP2_SLAVE_ERR_MASK)
			adsp_err(dsp, "bus error: slave error\n");
		else
			adsp_err(dsp, "bus error: region lock error\n");

		ret = regmap_read(regmap, dsp->base + ADSP2_BUS_ERR_ADDR, &val);
		if (ret) {
			adsp_err(dsp,
				 "Failed to read Bus Err Addr register: %d\n",
				 ret);
			return IRQ_HANDLED;
		}

		adsp_err(dsp, "bus error address = 0x%x\n",
			 val & ADSP2_BUS_ERR_ADDR_MASK);

		ret = regmap_read(regmap,
				  dsp->base + ADSP2_PMEM_ERR_ADDR_XMEM_ERR_ADDR,
				  &val);
		if (ret) {
			adsp_err(dsp,
				 "Failed to read Pmem Xmem Err Addr register: %d\n",
				 ret);
			return IRQ_HANDLED;
		}

		adsp_err(dsp, "xmem error address = 0x%x\n",
			 val & ADSP2_XMEM_ERR_ADDR_MASK);
		adsp_err(dsp, "pmem error address = 0x%x\n",
			 (val & ADSP2_PMEM_ERR_ADDR_MASK) >>
			 ADSP2_PMEM_ERR_ADDR_SHIFT);
	}

	regmap_update_bits(regmap, dsp->base + ADSP2_LOCK_REGION_CTRL,
			   ADSP2_CTRL_ERR_EINT, ADSP2_CTRL_ERR_EINT);

	return IRQ_HANDLED;
}