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
typedef  int u32 ;
struct mtk_thermal_data {int* sensor_mux_values; TYPE_1__* bank_data; scalar_t__* adcpnp; int /*<<< orphan*/  auxadc_channel; } ;
struct mtk_thermal_bank {int id; struct mtk_thermal* mt; } ;
struct mtk_thermal {scalar_t__ thermal_base; struct mtk_thermal_data* conf; struct mtk_thermal_bank* banks; } ;
struct TYPE_2__ {int num_sensors; size_t* sensors; } ;

/* Variables and functions */
 int APMIXED_SYS_TS_CON1 ; 
 int AUXADC_CON1_CLR_V ; 
 int AUXADC_CON1_SET_V ; 
 int AUXADC_DATA (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMP_ADCEN ; 
 scalar_t__ TEMP_ADCENADDR ; 
 scalar_t__ TEMP_ADCMUX ; 
 scalar_t__ TEMP_ADCMUXADDR ; 
 scalar_t__ TEMP_ADCVALIDADDR ; 
 scalar_t__ TEMP_ADCVALIDMASK ; 
 int TEMP_ADCVALIDMASK_VALID_HIGH ; 
 int TEMP_ADCVALIDMASK_VALID_POS (int) ; 
 scalar_t__ TEMP_ADCVOLTADDR ; 
 scalar_t__ TEMP_ADCVOLTAGESHIFT ; 
 scalar_t__ TEMP_ADCWRITECTRL ; 
 int TEMP_ADCWRITECTRL_ADC_MUX_WRITE ; 
 int TEMP_ADCWRITECTRL_ADC_PNP_WRITE ; 
 scalar_t__ TEMP_AHBPOLL ; 
 int TEMP_AHBPOLL_ADC_POLL_INTERVAL (int) ; 
 scalar_t__ TEMP_AHBTO ; 
 scalar_t__ TEMP_MONCTL0 ; 
 scalar_t__ TEMP_MONCTL1 ; 
 int TEMP_MONCTL1_PERIOD_UNIT (int) ; 
 scalar_t__ TEMP_MONCTL2 ; 
 int TEMP_MONCTL2_FILTER_INTERVAL (int) ; 
 int TEMP_MONCTL2_SENSOR_INTERVAL (int) ; 
 scalar_t__ TEMP_MONIDET0 ; 
 scalar_t__ TEMP_MONIDET1 ; 
 scalar_t__ TEMP_MSRCTL0 ; 
 scalar_t__ TEMP_PNPMUXADDR ; 
 scalar_t__ TEMP_RDCTRL ; 
 int /*<<< orphan*/  mtk_thermal_get_bank (struct mtk_thermal_bank*) ; 
 int /*<<< orphan*/  mtk_thermal_put_bank (struct mtk_thermal_bank*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_thermal_init_bank(struct mtk_thermal *mt, int num,
				  u32 apmixed_phys_base, u32 auxadc_phys_base)
{
	struct mtk_thermal_bank *bank = &mt->banks[num];
	const struct mtk_thermal_data *conf = mt->conf;
	int i;

	bank->id = num;
	bank->mt = mt;

	mtk_thermal_get_bank(bank);

	/* bus clock 66M counting unit is 12 * 15.15ns * 256 = 46.540us */
	writel(TEMP_MONCTL1_PERIOD_UNIT(12), mt->thermal_base + TEMP_MONCTL1);

	/*
	 * filt interval is 1 * 46.540us = 46.54us,
	 * sen interval is 429 * 46.540us = 19.96ms
	 */
	writel(TEMP_MONCTL2_FILTER_INTERVAL(1) |
			TEMP_MONCTL2_SENSOR_INTERVAL(429),
			mt->thermal_base + TEMP_MONCTL2);

	/* poll is set to 10u */
	writel(TEMP_AHBPOLL_ADC_POLL_INTERVAL(768),
	       mt->thermal_base + TEMP_AHBPOLL);

	/* temperature sampling control, 1 sample */
	writel(0x0, mt->thermal_base + TEMP_MSRCTL0);

	/* exceed this polling time, IRQ would be inserted */
	writel(0xffffffff, mt->thermal_base + TEMP_AHBTO);

	/* number of interrupts per event, 1 is enough */
	writel(0x0, mt->thermal_base + TEMP_MONIDET0);
	writel(0x0, mt->thermal_base + TEMP_MONIDET1);

	/*
	 * The MT8173 thermal controller does not have its own ADC. Instead it
	 * uses AHB bus accesses to control the AUXADC. To do this the thermal
	 * controller has to be programmed with the physical addresses of the
	 * AUXADC registers and with the various bit positions in the AUXADC.
	 * Also the thermal controller controls a mux in the APMIXEDSYS register
	 * space.
	 */

	/*
	 * this value will be stored to TEMP_PNPMUXADDR (TEMP_SPARE0)
	 * automatically by hw
	 */
	writel(BIT(conf->auxadc_channel), mt->thermal_base + TEMP_ADCMUX);

	/* AHB address for auxadc mux selection */
	writel(auxadc_phys_base + AUXADC_CON1_CLR_V,
	       mt->thermal_base + TEMP_ADCMUXADDR);

	/* AHB address for pnp sensor mux selection */
	writel(apmixed_phys_base + APMIXED_SYS_TS_CON1,
	       mt->thermal_base + TEMP_PNPMUXADDR);

	/* AHB value for auxadc enable */
	writel(BIT(conf->auxadc_channel), mt->thermal_base + TEMP_ADCEN);

	/* AHB address for auxadc enable (channel 0 immediate mode selected) */
	writel(auxadc_phys_base + AUXADC_CON1_SET_V,
	       mt->thermal_base + TEMP_ADCENADDR);

	/* AHB address for auxadc valid bit */
	writel(auxadc_phys_base + AUXADC_DATA(conf->auxadc_channel),
	       mt->thermal_base + TEMP_ADCVALIDADDR);

	/* AHB address for auxadc voltage output */
	writel(auxadc_phys_base + AUXADC_DATA(conf->auxadc_channel),
	       mt->thermal_base + TEMP_ADCVOLTADDR);

	/* read valid & voltage are at the same register */
	writel(0x0, mt->thermal_base + TEMP_RDCTRL);

	/* indicate where the valid bit is */
	writel(TEMP_ADCVALIDMASK_VALID_HIGH | TEMP_ADCVALIDMASK_VALID_POS(12),
	       mt->thermal_base + TEMP_ADCVALIDMASK);

	/* no shift */
	writel(0x0, mt->thermal_base + TEMP_ADCVOLTAGESHIFT);

	/* enable auxadc mux write transaction */
	writel(TEMP_ADCWRITECTRL_ADC_MUX_WRITE,
	       mt->thermal_base + TEMP_ADCWRITECTRL);

	for (i = 0; i < conf->bank_data[num].num_sensors; i++)
		writel(conf->sensor_mux_values[conf->bank_data[num].sensors[i]],
		       mt->thermal_base + conf->adcpnp[i]);

	writel((1 << conf->bank_data[num].num_sensors) - 1,
	       mt->thermal_base + TEMP_MONCTL0);

	writel(TEMP_ADCWRITECTRL_ADC_PNP_WRITE |
	       TEMP_ADCWRITECTRL_ADC_MUX_WRITE,
	       mt->thermal_base + TEMP_ADCWRITECTRL);

	mtk_thermal_put_bank(bank);
}