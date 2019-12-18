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
struct wm_adsp {unsigned int base; struct regmap* regmap; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int ADSP2_LOCK_CODE_0 ; 
 unsigned int ADSP2_LOCK_CODE_1 ; 
 unsigned int ADSP2_LOCK_REGION_1_LOCK_REGION_0 ; 
 unsigned int ADSP2_LOCK_REGION_SHIFT ; 
 unsigned int BIT (int) ; 
 unsigned int WM_ADSP2_REGION_ALL ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm_adsp2_lock(struct wm_adsp *dsp, unsigned int lock_regions)
{
	struct regmap *regmap = dsp->regmap;
	unsigned int code0, code1, lock_reg;

	if (!(lock_regions & WM_ADSP2_REGION_ALL))
		return 0;

	lock_regions &= WM_ADSP2_REGION_ALL;
	lock_reg = dsp->base + ADSP2_LOCK_REGION_1_LOCK_REGION_0;

	while (lock_regions) {
		code0 = code1 = 0;
		if (lock_regions & BIT(0)) {
			code0 = ADSP2_LOCK_CODE_0;
			code1 = ADSP2_LOCK_CODE_1;
		}
		if (lock_regions & BIT(1)) {
			code0 |= ADSP2_LOCK_CODE_0 << ADSP2_LOCK_REGION_SHIFT;
			code1 |= ADSP2_LOCK_CODE_1 << ADSP2_LOCK_REGION_SHIFT;
		}
		regmap_write(regmap, lock_reg, code0);
		regmap_write(regmap, lock_reg, code1);
		lock_regions >>= 2;
		lock_reg += 2;
	}

	return 0;
}