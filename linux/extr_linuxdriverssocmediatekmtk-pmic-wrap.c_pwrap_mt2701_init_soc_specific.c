#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmic_wrapper {TYPE_1__* slave; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  PMIC_MT6323 128 
 int /*<<< orphan*/  PWRAP_ADC_CMD_ADDR ; 
 int /*<<< orphan*/  PWRAP_ADC_RDATA_ADDR1 ; 
 int /*<<< orphan*/  PWRAP_ADC_RDATA_ADDR2 ; 
 int /*<<< orphan*/  PWRAP_ADC_RDY_ADDR ; 
 int /*<<< orphan*/  PWRAP_PWRAP_ADC_CMD ; 
 int /*<<< orphan*/  pwrap_writel (struct pmic_wrapper*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pwrap_mt2701_init_soc_specific(struct pmic_wrapper *wrp)
{
	/* GPS_INTF initialization */
	switch (wrp->slave->type) {
	case PMIC_MT6323:
		pwrap_writel(wrp, 0x076c, PWRAP_ADC_CMD_ADDR);
		pwrap_writel(wrp, 0x8000, PWRAP_PWRAP_ADC_CMD);
		pwrap_writel(wrp, 0x072c, PWRAP_ADC_RDY_ADDR);
		pwrap_writel(wrp, 0x072e, PWRAP_ADC_RDATA_ADDR1);
		pwrap_writel(wrp, 0x0730, PWRAP_ADC_RDATA_ADDR2);
		break;
	default:
		break;
	}

	return 0;
}