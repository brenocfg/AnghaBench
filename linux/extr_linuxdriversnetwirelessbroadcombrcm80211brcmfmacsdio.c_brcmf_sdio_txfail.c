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
typedef  int u8 ;
struct brcmf_sdio_dev {int /*<<< orphan*/  func2; } ;
struct TYPE_2__ {scalar_t__ f1regdata; int /*<<< orphan*/  tx_sderrs; } ;
struct brcmf_sdio {TYPE_1__ sdcnt; struct brcmf_sdio_dev* sdiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBSDIO_FUNC1_FRAMECTRL ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_WFRAMEBCHI ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_WFRAMEBCLO ; 
 int /*<<< orphan*/  SFC_WF_TERM ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_sdiod_abort (struct brcmf_sdio_dev*,int /*<<< orphan*/ ) ; 
 int brcmf_sdiod_readb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_sdio_txfail(struct brcmf_sdio *bus)
{
	struct brcmf_sdio_dev *sdiodev = bus->sdiodev;
	u8 i, hi, lo;

	/* On failure, abort the command and terminate the frame */
	brcmf_err("sdio error, abort command and terminate frame\n");
	bus->sdcnt.tx_sderrs++;

	brcmf_sdiod_abort(sdiodev, sdiodev->func2);
	brcmf_sdiod_writeb(sdiodev, SBSDIO_FUNC1_FRAMECTRL, SFC_WF_TERM, NULL);
	bus->sdcnt.f1regdata++;

	for (i = 0; i < 3; i++) {
		hi = brcmf_sdiod_readb(sdiodev, SBSDIO_FUNC1_WFRAMEBCHI, NULL);
		lo = brcmf_sdiod_readb(sdiodev, SBSDIO_FUNC1_WFRAMEBCLO, NULL);
		bus->sdcnt.f1regdata += 2;
		if ((hi == 0) && (lo == 0))
			break;
	}
}