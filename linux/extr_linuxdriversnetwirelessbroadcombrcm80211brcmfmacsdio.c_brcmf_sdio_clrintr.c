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
struct brcmf_sdio_dev {int irq_en; int /*<<< orphan*/  irq_en_lock; TYPE_3__* settings; scalar_t__ oob_irq_requested; } ;
struct brcmf_sdio {int /*<<< orphan*/  ipend; struct brcmf_sdio_dev* sdiodev; } ;
struct TYPE_4__ {int /*<<< orphan*/  oob_irq_nr; } ;
struct TYPE_5__ {TYPE_1__ sdio; } ;
struct TYPE_6__ {TYPE_2__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void brcmf_sdio_clrintr(struct brcmf_sdio *bus)
{
	struct brcmf_sdio_dev *sdiodev;
	unsigned long flags;

	sdiodev = bus->sdiodev;
	if (sdiodev->oob_irq_requested) {
		spin_lock_irqsave(&sdiodev->irq_en_lock, flags);
		if (!sdiodev->irq_en && !atomic_read(&bus->ipend)) {
			enable_irq(sdiodev->settings->bus.sdio.oob_irq_nr);
			sdiodev->irq_en = true;
		}
		spin_unlock_irqrestore(&sdiodev->irq_en_lock, flags);
	}
}