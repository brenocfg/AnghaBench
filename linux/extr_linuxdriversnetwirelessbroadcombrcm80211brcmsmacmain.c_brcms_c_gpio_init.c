#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct brcms_hardware {scalar_t__ antsel_type; int boardflags; TYPE_3__* d11core; TYPE_1__* band; } ;
struct brcms_c_info {struct brcms_hardware* hw; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  drv_cc; } ;
struct TYPE_4__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 scalar_t__ ANTSEL_2x4 ; 
 int /*<<< orphan*/  ANTSEL_CLKDIV_4MHZ ; 
 int BFL_PACTRL ; 
 int BOARD_GPIO_12 ; 
 int BOARD_GPIO_13 ; 
 int BOARD_GPIO_PACTRL ; 
 int /*<<< orphan*/  BRCM_BAND_ALL ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCTL_GPOUT_SEL_MASK ; 
 int /*<<< orphan*/  MHF3 ; 
 int /*<<< orphan*/  MHF3_ANTSEL_EN ; 
 int /*<<< orphan*/  MHF3_ANTSEL_MODE ; 
 int /*<<< orphan*/  M_ANTSEL_CLKDIV ; 
 int /*<<< orphan*/  bcma_chipco_gpio_control (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bcma_set16 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_b_mctrl (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_mhf (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psm_gpio_oe ; 
 int /*<<< orphan*/  psm_gpio_out ; 
 int /*<<< orphan*/  wlc_phy_antsel_init (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_c_gpio_init(struct brcms_c_info *wlc)
{
	struct brcms_hardware *wlc_hw = wlc->hw;
	u32 gc, gm;

	/* use GPIO select 0 to get all gpio signals from the gpio out reg */
	brcms_b_mctrl(wlc_hw, MCTL_GPOUT_SEL_MASK, 0);

	/*
	 * Common GPIO setup:
	 *      G0 = LED 0 = WLAN Activity
	 *      G1 = LED 1 = WLAN 2.4 GHz Radio State
	 *      G2 = LED 2 = WLAN 5 GHz Radio State
	 *      G4 = radio disable input (HI enabled, LO disabled)
	 */

	gc = gm = 0;

	/* Allocate GPIOs for mimo antenna diversity feature */
	if (wlc_hw->antsel_type == ANTSEL_2x3) {
		/* Enable antenna diversity, use 2x3 mode */
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_EN,
			     MHF3_ANTSEL_EN, BRCM_BAND_ALL);
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_MODE,
			     MHF3_ANTSEL_MODE, BRCM_BAND_ALL);

		/* init superswitch control */
		wlc_phy_antsel_init(wlc_hw->band->pi, false);

	} else if (wlc_hw->antsel_type == ANTSEL_2x4) {
		gm |= gc |= (BOARD_GPIO_12 | BOARD_GPIO_13);
		/*
		 * The board itself is powered by these GPIOs
		 * (when not sending pattern) so set them high
		 */
		bcma_set16(wlc_hw->d11core, D11REGOFFS(psm_gpio_oe),
			   (BOARD_GPIO_12 | BOARD_GPIO_13));
		bcma_set16(wlc_hw->d11core, D11REGOFFS(psm_gpio_out),
			   (BOARD_GPIO_12 | BOARD_GPIO_13));

		/* Enable antenna diversity, use 2x4 mode */
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_EN,
			     MHF3_ANTSEL_EN, BRCM_BAND_ALL);
		brcms_b_mhf(wlc_hw, MHF3, MHF3_ANTSEL_MODE, 0,
			     BRCM_BAND_ALL);

		/* Configure the desired clock to be 4Mhz */
		brcms_b_write_shm(wlc_hw, M_ANTSEL_CLKDIV,
				   ANTSEL_CLKDIV_4MHZ);
	}

	/*
	 * gpio 9 controls the PA. ucode is responsible
	 * for wiggling out and oe
	 */
	if (wlc_hw->boardflags & BFL_PACTRL)
		gm |= gc |= BOARD_GPIO_PACTRL;

	/* apply to gpiocontrol register */
	bcma_chipco_gpio_control(&wlc_hw->d11core->bus->drv_cc, gm, gc);
}