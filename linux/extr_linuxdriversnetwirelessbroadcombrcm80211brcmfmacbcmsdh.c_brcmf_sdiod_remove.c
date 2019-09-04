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
struct brcmf_sdio_dev {TYPE_3__* func1; scalar_t__ sbwad; int /*<<< orphan*/  sgtable; TYPE_3__* func2; int /*<<< orphan*/ * bus; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_2__* card; } ;
struct TYPE_7__ {TYPE_1__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_SDIOD_DOWN ; 
 int /*<<< orphan*/  brcmf_sdio_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_sdiod_freezer_detach (struct brcmf_sdio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_3__*) ; 
 int /*<<< orphan*/  sdio_disable_func (TYPE_3__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_3__*) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_sdiod_remove(struct brcmf_sdio_dev *sdiodev)
{
	sdiodev->state = BRCMF_SDIOD_DOWN;
	if (sdiodev->bus) {
		brcmf_sdio_remove(sdiodev->bus);
		sdiodev->bus = NULL;
	}

	brcmf_sdiod_freezer_detach(sdiodev);

	/* Disable Function 2 */
	sdio_claim_host(sdiodev->func2);
	sdio_disable_func(sdiodev->func2);
	sdio_release_host(sdiodev->func2);

	/* Disable Function 1 */
	sdio_claim_host(sdiodev->func1);
	sdio_disable_func(sdiodev->func1);
	sdio_release_host(sdiodev->func1);

	sg_free_table(&sdiodev->sgtable);
	sdiodev->sbwad = 0;

	pm_runtime_allow(sdiodev->func1->card->host->parent);
	return 0;
}