#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct prcm_gpiocr_altcx_pin_desc {unsigned int pin; TYPE_2__* altcx; } ;
struct nmk_pinctrl {scalar_t__ prcm_base; int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct TYPE_4__ {int used; size_t reg_index; size_t control_bit; } ;
struct TYPE_3__ {int npins_altcx; scalar_t__* prcm_gpiocr_registers; struct prcm_gpiocr_altcx_pin_desc* altcx_pins; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 unsigned int PRCM_IDX_GPIOCR_ALTC_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nmk_write_masked (scalar_t__,int,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void nmk_prcm_altcx_set_mode(struct nmk_pinctrl *npct,
	unsigned offset, unsigned alt_num)
{
	int i;
	u16 reg;
	u8 bit;
	u8 alt_index;
	const struct prcm_gpiocr_altcx_pin_desc *pin_desc;
	const u16 *gpiocr_regs;

	if (!npct->prcm_base)
		return;

	if (alt_num > PRCM_IDX_GPIOCR_ALTC_MAX) {
		dev_err(npct->dev, "PRCM GPIOCR: alternate-C%i is invalid\n",
			alt_num);
		return;
	}

	for (i = 0 ; i < npct->soc->npins_altcx ; i++) {
		if (npct->soc->altcx_pins[i].pin == offset)
			break;
	}
	if (i == npct->soc->npins_altcx) {
		dev_dbg(npct->dev, "PRCM GPIOCR: pin %i is not found\n",
			offset);
		return;
	}

	pin_desc = npct->soc->altcx_pins + i;
	gpiocr_regs = npct->soc->prcm_gpiocr_registers;

	/*
	 * If alt_num is NULL, just clear current ALTCx selection
	 * to make sure we come back to a pure ALTC selection
	 */
	if (!alt_num) {
		for (i = 0 ; i < PRCM_IDX_GPIOCR_ALTC_MAX ; i++) {
			if (pin_desc->altcx[i].used == true) {
				reg = gpiocr_regs[pin_desc->altcx[i].reg_index];
				bit = pin_desc->altcx[i].control_bit;
				if (readl(npct->prcm_base + reg) & BIT(bit)) {
					nmk_write_masked(npct->prcm_base + reg, BIT(bit), 0);
					dev_dbg(npct->dev,
						"PRCM GPIOCR: pin %i: alternate-C%i has been disabled\n",
						offset, i+1);
				}
			}
		}
		return;
	}

	alt_index = alt_num - 1;
	if (pin_desc->altcx[alt_index].used == false) {
		dev_warn(npct->dev,
			"PRCM GPIOCR: pin %i: alternate-C%i does not exist\n",
			offset, alt_num);
		return;
	}

	/*
	 * Check if any other ALTCx functions are activated on this pin
	 * and disable it first.
	 */
	for (i = 0 ; i < PRCM_IDX_GPIOCR_ALTC_MAX ; i++) {
		if (i == alt_index)
			continue;
		if (pin_desc->altcx[i].used == true) {
			reg = gpiocr_regs[pin_desc->altcx[i].reg_index];
			bit = pin_desc->altcx[i].control_bit;
			if (readl(npct->prcm_base + reg) & BIT(bit)) {
				nmk_write_masked(npct->prcm_base + reg, BIT(bit), 0);
				dev_dbg(npct->dev,
					"PRCM GPIOCR: pin %i: alternate-C%i has been disabled\n",
					offset, i+1);
			}
		}
	}

	reg = gpiocr_regs[pin_desc->altcx[alt_index].reg_index];
	bit = pin_desc->altcx[alt_index].control_bit;
	dev_dbg(npct->dev, "PRCM GPIOCR: pin %i: alternate-C%i has been selected\n",
		offset, alt_index+1);
	nmk_write_masked(npct->prcm_base + reg, BIT(bit), BIT(bit));
}