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
typedef  int u8 ;
struct brcmf_sdio {int sr_enabled; int /*<<< orphan*/  sdiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int SBSDIO_FORCE_HT ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_WAKEUPCTRL ; 
 int SBSDIO_FUNC1_WCTRL_HTWAIT_SHIFT ; 
 int /*<<< orphan*/  SDIO_CCCR_BRCM_CARDCAP ; 
 int SDIO_CCCR_BRCM_CARDCAP_CMD14_EXT ; 
 int SDIO_CCCR_BRCM_CARDCAP_CMD14_SUPPORT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_sdiod_func0_wb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int brcmf_sdiod_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void brcmf_sdio_sr_init(struct brcmf_sdio *bus)
{
	int err = 0;
	u8 val;

	brcmf_dbg(TRACE, "Enter\n");

	val = brcmf_sdiod_readb(bus->sdiodev, SBSDIO_FUNC1_WAKEUPCTRL, &err);
	if (err) {
		brcmf_err("error reading SBSDIO_FUNC1_WAKEUPCTRL\n");
		return;
	}

	val |= 1 << SBSDIO_FUNC1_WCTRL_HTWAIT_SHIFT;
	brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_WAKEUPCTRL, val, &err);
	if (err) {
		brcmf_err("error writing SBSDIO_FUNC1_WAKEUPCTRL\n");
		return;
	}

	/* Add CMD14 Support */
	brcmf_sdiod_func0_wb(bus->sdiodev, SDIO_CCCR_BRCM_CARDCAP,
			     (SDIO_CCCR_BRCM_CARDCAP_CMD14_SUPPORT |
			      SDIO_CCCR_BRCM_CARDCAP_CMD14_EXT),
			     &err);
	if (err) {
		brcmf_err("error writing SDIO_CCCR_BRCM_CARDCAP\n");
		return;
	}

	brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
			   SBSDIO_FORCE_HT, &err);
	if (err) {
		brcmf_err("error writing SBSDIO_FUNC1_CHIPCLKCSR\n");
		return;
	}

	/* set flag */
	bus->sr_enabled = true;
	brcmf_dbg(INFO, "SR enabled\n");
}