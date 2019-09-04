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
struct brcmf_sdio_dev {int irq_en; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_sdio_isr (int /*<<< orphan*/ ) ; 
 struct brcmf_bus* dev_get_drvdata (void*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 

__attribute__((used)) static irqreturn_t brcmf_sdiod_oob_irqhandler(int irq, void *dev_id)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev_id);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;

	brcmf_dbg(INTR, "OOB intr triggered\n");

	/* out-of-band interrupt is level-triggered which won't
	 * be cleared until dpc
	 */
	if (sdiodev->irq_en) {
		disable_irq_nosync(irq);
		sdiodev->irq_en = false;
	}

	brcmf_sdio_isr(sdiodev->bus);

	return IRQ_HANDLED;
}