#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_ali {TYPE_1__* card; TYPE_2__* pci; int /*<<< orphan*/  irq; int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pci_request_regions (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_ali*) ; 
 int /*<<< orphan*/  snd_ali_card_interrupt ; 

__attribute__((used)) static int snd_ali_resources(struct snd_ali *codec)
{
	int err;

	dev_dbg(codec->card->dev, "resources allocation ...\n");
	err = pci_request_regions(codec->pci, "ALI 5451");
	if (err < 0)
		return err;
	codec->port = pci_resource_start(codec->pci, 0);

	if (request_irq(codec->pci->irq, snd_ali_card_interrupt,
			IRQF_SHARED, KBUILD_MODNAME, codec)) {
		dev_err(codec->card->dev, "Unable to request irq.\n");
		return -EBUSY;
	}
	codec->irq = codec->pci->irq;
	dev_dbg(codec->card->dev, "resources allocated.\n");
	return 0;
}