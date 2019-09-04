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
struct msdc_hw {int flags; int /*<<< orphan*/  (* config_gpio_pin ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct msdc_host {scalar_t__ base; struct msdc_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  DEFAULT_DEBOUNCE ; 
 int /*<<< orphan*/  GPIO_PULL_DOWN ; 
 int /*<<< orphan*/  GPIO_PULL_UP ; 
 int /*<<< orphan*/  MSDC_CD_PIN ; 
 int MSDC_CD_PIN_EN ; 
 scalar_t__ MSDC_INTEN ; 
 int /*<<< orphan*/  MSDC_INTEN_CDSC ; 
 scalar_t__ MSDC_PS ; 
 int /*<<< orphan*/  MSDC_PS_CDDEBOUNCE ; 
 int /*<<< orphan*/  MSDC_PS_CDEN ; 
 int /*<<< orphan*/  N_MSG (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ SDC_CFG ; 
 int /*<<< orphan*/  SDC_CFG_INSWKUP ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msdc_enable_cd_irq(struct msdc_host *host, int enable)
{
	struct msdc_hw *hw = host->hw;

	/* for sdio, not set */
	if ((hw->flags & MSDC_CD_PIN_EN) == 0) {
		/* Pull down card detection pin since it is not avaiable */
		/*
		  if (hw->config_gpio_pin)
		  hw->config_gpio_pin(MSDC_CD_PIN, GPIO_PULL_DOWN);
		*/
		sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_clr_bits(host->base + MSDC_INTEN, MSDC_INTEN_CDSC);
		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
		return;
	}

	N_MSG(CFG, "CD IRQ Enable(%d)", enable);

	if (enable) {
		/* card detection circuit relies on the core power so that the core power
		 * shouldn't be turned off. Here adds a reference count to keep
		 * the core power alive.
		 */
		//msdc_vcore_on(host); //did in msdc_init_hw()

		if (hw->config_gpio_pin) /* NULL */
			hw->config_gpio_pin(MSDC_CD_PIN, GPIO_PULL_UP);

		sdr_set_field(host->base + MSDC_PS, MSDC_PS_CDDEBOUNCE,
			      DEFAULT_DEBOUNCE);
		sdr_set_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_set_bits(host->base + MSDC_INTEN, MSDC_INTEN_CDSC);

		/* not in document! Fix me */
		sdr_set_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
	} else {
		if (hw->config_gpio_pin) /* NULL */
			hw->config_gpio_pin(MSDC_CD_PIN, GPIO_PULL_DOWN);

		sdr_clr_bits(host->base + SDC_CFG, SDC_CFG_INSWKUP);
		sdr_clr_bits(host->base + MSDC_PS, MSDC_PS_CDEN);
		sdr_clr_bits(host->base + MSDC_INTEN, MSDC_INTEN_CDSC);

		/* Here decreases a reference count to core power since card
		 * detection circuit is shutdown.
		 */
		//msdc_vcore_off(host);
	}
}