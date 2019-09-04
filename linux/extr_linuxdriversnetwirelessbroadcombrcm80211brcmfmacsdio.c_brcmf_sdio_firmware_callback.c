#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;
struct brcmf_sdio_dev {TYPE_6__* func2; int /*<<< orphan*/  func1; int /*<<< orphan*/  settings; int /*<<< orphan*/  dev; TYPE_5__* bus_if; struct brcmf_sdio* bus; } ;
struct TYPE_12__ {scalar_t__ tickcnt; } ;
struct brcmf_sdio {int alp_only; scalar_t__ clkstate; int hostintmask; TYPE_8__* ci; int /*<<< orphan*/  sdiodev; TYPE_4__ sdcnt; struct brcmf_core* sdio_core; } ;
struct brcmf_fw_request {TYPE_3__* items; } ;
struct brcmf_core {scalar_t__ base; } ;
struct TYPE_9__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;
struct TYPE_15__ {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;
struct TYPE_14__ {struct device dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; int /*<<< orphan*/ * ops; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; void* data; } ;
struct TYPE_11__ {TYPE_2__ nv_data; struct firmware* binary; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_SDIOD_DATA ; 
 size_t BRCMF_SDIO_FW_CODE ; 
 size_t BRCMF_SDIO_FW_NVRAM ; 
 scalar_t__ CLK_AVAIL ; 
 scalar_t__ CLK_NONE ; 
 int HOSTINTMASK ; 
 int /*<<< orphan*/  INFO ; 
 int SBSDIO_FORCE_HT ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 int /*<<< orphan*/  SBSDIO_WATERMARK ; 
 int SDPCM_PROT_VERSION ; 
 scalar_t__ SD_REG (int /*<<< orphan*/ ) ; 
 int SMB_DATA_VERSION_SHIFT ; 
 int /*<<< orphan*/  TRACE ; 
 int brcmf_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ brcmf_chip_sr_capable (TYPE_8__*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int /*<<< orphan*/  brcmf_sdio_bus_ops ; 
 int /*<<< orphan*/  brcmf_sdio_clkctl (struct brcmf_sdio*,scalar_t__,int) ; 
 int brcmf_sdio_download_firmware (struct brcmf_sdio*,struct firmware const*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdio_sr_init (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_wd_timer (struct brcmf_sdio*,int) ; 
 int /*<<< orphan*/  brcmf_sdiod_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_sdiod_intr_register (struct brcmf_sdio_dev*) ; 
 int brcmf_sdiod_readb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writel (struct brcmf_sdio_dev*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  hostintmask ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw_request*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (TYPE_6__*) ; 
 int sdio_enable_func (TYPE_6__*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tosbmailboxdata ; 

__attribute__((used)) static void brcmf_sdio_firmware_callback(struct device *dev, int err,
					 struct brcmf_fw_request *fwreq)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiod = bus_if->bus_priv.sdio;
	struct brcmf_sdio *bus = sdiod->bus;
	struct brcmf_core *core = bus->sdio_core;
	const struct firmware *code;
	void *nvram;
	u32 nvram_len;
	u8 saveclk;

	brcmf_dbg(TRACE, "Enter: dev=%s, err=%d\n", dev_name(dev), err);

	if (err)
		goto fail;

	code = fwreq->items[BRCMF_SDIO_FW_CODE].binary;
	nvram = fwreq->items[BRCMF_SDIO_FW_NVRAM].nv_data.data;
	nvram_len = fwreq->items[BRCMF_SDIO_FW_NVRAM].nv_data.len;
	kfree(fwreq);

	/* try to download image and nvram to the dongle */
	bus->alp_only = true;
	err = brcmf_sdio_download_firmware(bus, code, nvram, nvram_len);
	if (err)
		goto fail;
	bus->alp_only = false;

	/* Start the watchdog timer */
	bus->sdcnt.tickcnt = 0;
	brcmf_sdio_wd_timer(bus, true);

	sdio_claim_host(sdiod->func1);

	/* Make sure backplane clock is on, needed to generate F2 interrupt */
	brcmf_sdio_clkctl(bus, CLK_AVAIL, false);
	if (bus->clkstate != CLK_AVAIL)
		goto release;

	/* Force clocks on backplane to be sure F2 interrupt propagates */
	saveclk = brcmf_sdiod_readb(sdiod, SBSDIO_FUNC1_CHIPCLKCSR, &err);
	if (!err) {
		brcmf_sdiod_writeb(sdiod, SBSDIO_FUNC1_CHIPCLKCSR,
				   (saveclk | SBSDIO_FORCE_HT), &err);
	}
	if (err) {
		brcmf_err("Failed to force clock for F2: err %d\n", err);
		goto release;
	}

	/* Enable function 2 (frame transfers) */
	brcmf_sdiod_writel(sdiod, core->base + SD_REG(tosbmailboxdata),
			   SDPCM_PROT_VERSION << SMB_DATA_VERSION_SHIFT, NULL);

	err = sdio_enable_func(sdiod->func2);

	brcmf_dbg(INFO, "enable F2: err=%d\n", err);

	/* If F2 successfully enabled, set core and enable interrupts */
	if (!err) {
		/* Set up the interrupt mask and enable interrupts */
		bus->hostintmask = HOSTINTMASK;
		brcmf_sdiod_writel(sdiod, core->base + SD_REG(hostintmask),
				   bus->hostintmask, NULL);


		brcmf_sdiod_writeb(sdiod, SBSDIO_WATERMARK, 8, &err);
	} else {
		/* Disable F2 again */
		sdio_disable_func(sdiod->func2);
		goto release;
	}

	if (brcmf_chip_sr_capable(bus->ci)) {
		brcmf_sdio_sr_init(bus);
	} else {
		/* Restore previous clock setting */
		brcmf_sdiod_writeb(sdiod, SBSDIO_FUNC1_CHIPCLKCSR,
				   saveclk, &err);
	}

	if (err == 0) {
		/* Allow full data communication using DPC from now on. */
		brcmf_sdiod_change_state(bus->sdiodev, BRCMF_SDIOD_DATA);

		err = brcmf_sdiod_intr_register(sdiod);
		if (err != 0)
			brcmf_err("intr register failed:%d\n", err);
	}

	/* If we didn't come up, turn off backplane clock */
	if (err != 0)
		brcmf_sdio_clkctl(bus, CLK_NONE, false);

	sdio_release_host(sdiod->func1);

	/* Assign bus interface call back */
	sdiod->bus_if->dev = sdiod->dev;
	sdiod->bus_if->ops = &brcmf_sdio_bus_ops;
	sdiod->bus_if->chip = bus->ci->chip;
	sdiod->bus_if->chiprev = bus->ci->chiprev;

	/* Attach to the common layer, reserve hdr space */
	err = brcmf_attach(sdiod->dev, sdiod->settings);
	if (err != 0) {
		brcmf_err("brcmf_attach failed\n");
		goto fail;
	}

	/* ready */
	return;

release:
	sdio_release_host(sdiod->func1);
fail:
	brcmf_dbg(TRACE, "failed: dev=%s, err=%d\n", dev_name(dev), err);
	device_release_driver(&sdiod->func2->dev);
	device_release_driver(dev);
}