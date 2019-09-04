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
struct brcmf_sdio {int sleeping; scalar_t__ sr_enabled; int /*<<< orphan*/  sdiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_AVAIL ; 
 int /*<<< orphan*/  CLK_NONE ; 
 int /*<<< orphan*/  SBSDIO_ALP_AVAIL_REQ ; 
 int SBSDIO_CSR_MASK ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_sdio_clkctl (struct brcmf_sdio*,int /*<<< orphan*/ ,int) ; 
 int brcmf_sdio_kso_control (struct brcmf_sdio*,int) ; 
 int /*<<< orphan*/  brcmf_sdio_wd_timer (struct brcmf_sdio*,int) ; 
 int brcmf_sdiod_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
brcmf_sdio_bus_sleep(struct brcmf_sdio *bus, bool sleep, bool pendok)
{
	int err = 0;
	u8 clkcsr;

	brcmf_dbg(SDIO, "Enter: request %s currently %s\n",
		  (sleep ? "SLEEP" : "WAKE"),
		  (bus->sleeping ? "SLEEP" : "WAKE"));

	/* If SR is enabled control bus state with KSO */
	if (bus->sr_enabled) {
		/* Done if we're already in the requested state */
		if (sleep == bus->sleeping)
			goto end;

		/* Going to sleep */
		if (sleep) {
			clkcsr = brcmf_sdiod_readb(bus->sdiodev,
						   SBSDIO_FUNC1_CHIPCLKCSR,
						   &err);
			if ((clkcsr & SBSDIO_CSR_MASK) == 0) {
				brcmf_dbg(SDIO, "no clock, set ALP\n");
				brcmf_sdiod_writeb(bus->sdiodev,
						   SBSDIO_FUNC1_CHIPCLKCSR,
						   SBSDIO_ALP_AVAIL_REQ, &err);
			}
			err = brcmf_sdio_kso_control(bus, false);
		} else {
			err = brcmf_sdio_kso_control(bus, true);
		}
		if (err) {
			brcmf_err("error while changing bus sleep state %d\n",
				  err);
			goto done;
		}
	}

end:
	/* control clocks */
	if (sleep) {
		if (!bus->sr_enabled)
			brcmf_sdio_clkctl(bus, CLK_NONE, pendok);
	} else {
		brcmf_sdio_clkctl(bus, CLK_AVAIL, pendok);
		brcmf_sdio_wd_timer(bus, true);
	}
	bus->sleeping = sleep;
	brcmf_dbg(SDIO, "new state %s\n",
		  (sleep ? "SLEEP" : "WAKE"));
done:
	brcmf_dbg(SDIO, "Exit: err=%d\n", err);
	return err;

}