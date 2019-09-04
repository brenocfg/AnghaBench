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
typedef  int u32 ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGU_ODR ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pm80xx_chip_is_our_interupt(struct pm8001_hba_info *pm8001_ha)
{
	u32 value;
#ifdef PM8001_USE_MSIX
	return 1;
#endif
	value = pm8001_cr32(pm8001_ha, 0, MSGU_ODR);
	if (value)
		return 1;
	return 0;

}