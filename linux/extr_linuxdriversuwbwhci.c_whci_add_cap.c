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
typedef  int /*<<< orphan*/  u64 ;
struct whci_card {struct umc_dev** devs; TYPE_3__* pci; scalar_t__ uwbbase; } ;
struct TYPE_4__ {int start; int end; TYPE_2__* parent; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct umc_dev {int bar; int /*<<< orphan*/  irq; TYPE_1__ resource; int /*<<< orphan*/  dev; int /*<<< orphan*/  cap_id; int /*<<< orphan*/  version; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; TYPE_2__* resource; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ UWBCAPDATA (int) ; 
 int UWBCAPDATA_TO_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWBCAPDATA_TO_CAP_ID (int /*<<< orphan*/ ) ; 
 int UWBCAPDATA_TO_OFFSET (int /*<<< orphan*/ ) ; 
 int UWBCAPDATA_TO_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWBCAPDATA_TO_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct umc_dev*) ; 
 int /*<<< orphan*/  le_readq (scalar_t__) ; 
 int pci_resource_start (TYPE_3__*,int) ; 
 struct umc_dev* umc_device_create (int /*<<< orphan*/ *,int) ; 
 int umc_device_register (struct umc_dev*) ; 
 int /*<<< orphan*/  whci_capdata_quirks (struct whci_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int whci_add_cap(struct whci_card *card, int n)
{
	struct umc_dev *umc;
	u64 capdata;
	int bar, err;

	umc = umc_device_create(&card->pci->dev, n);
	if (umc == NULL)
		return -ENOMEM;

	capdata = le_readq(card->uwbbase + UWBCAPDATA(n));

	bar = UWBCAPDATA_TO_BAR(capdata) << 1;

	capdata = whci_capdata_quirks(card, capdata);
	/* Capability 0 is the radio controller. It's size is 32
	 * bytes (WHCI0.95[2.3, T2-9]). */
	umc->version         = UWBCAPDATA_TO_VERSION(capdata);
	umc->cap_id          = n == 0 ? 0 : UWBCAPDATA_TO_CAP_ID(capdata);
	umc->bar	     = bar;
	umc->resource.start  = pci_resource_start(card->pci, bar)
		+ UWBCAPDATA_TO_OFFSET(capdata);
	umc->resource.end    = umc->resource.start
		+ (n == 0 ? 0x20 : UWBCAPDATA_TO_SIZE(capdata)) - 1;
	umc->resource.name   = dev_name(&umc->dev);
	umc->resource.flags  = card->pci->resource[bar].flags;
	umc->resource.parent = &card->pci->resource[bar];
	umc->irq             = card->pci->irq;

	err = umc_device_register(umc);
	if (err < 0)
		goto error;
	card->devs[n] = umc;
	return 0;

error:
	kfree(umc);
	return err;
}