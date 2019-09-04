#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct brcmfmac_sdio_pd {int /*<<< orphan*/  oob_irq_nr; } ;
struct brcmf_sdio_dev {int oob_irq_requested; int sd_irq_requested; int irq_wake; int irq_en; TYPE_3__* func1; TYPE_3__* func2; TYPE_2__* settings; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct brcmfmac_sdio_pd sdio; } ;
struct TYPE_7__ {TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  SDIO_CCCR_BRCM_SEPINT ; 
 int /*<<< orphan*/  SDIO_CCCR_IENx ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  brcmf_sdiod_func0_wb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_3__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_3__*) ; 
 int /*<<< orphan*/  sdio_release_irq (TYPE_3__*) ; 

void brcmf_sdiod_intr_unregister(struct brcmf_sdio_dev *sdiodev)
{

	brcmf_dbg(SDIO, "Entering oob=%d sd=%d\n",
		  sdiodev->oob_irq_requested,
		  sdiodev->sd_irq_requested);

	if (sdiodev->oob_irq_requested) {
		struct brcmfmac_sdio_pd *pdata;

		pdata = &sdiodev->settings->bus.sdio;
		sdio_claim_host(sdiodev->func1);
		brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_BRCM_SEPINT, 0, NULL);
		brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_IENx, 0, NULL);
		sdio_release_host(sdiodev->func1);

		sdiodev->oob_irq_requested = false;
		if (sdiodev->irq_wake) {
			disable_irq_wake(pdata->oob_irq_nr);
			sdiodev->irq_wake = false;
		}
		free_irq(pdata->oob_irq_nr, &sdiodev->func1->dev);
		sdiodev->irq_en = false;
		sdiodev->oob_irq_requested = false;
	}

	if (sdiodev->sd_irq_requested) {
		sdio_claim_host(sdiodev->func1);
		sdio_release_irq(sdiodev->func2);
		sdio_release_irq(sdiodev->func1);
		sdio_release_host(sdiodev->func1);
		sdiodev->sd_irq_requested = false;
	}
}