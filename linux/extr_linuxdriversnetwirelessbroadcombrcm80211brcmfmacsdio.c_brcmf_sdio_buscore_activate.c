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
typedef  scalar_t__ u32 ;
struct brcmf_sdio_dev {TYPE_1__* bus; } ;
struct brcmf_core {scalar_t__ base; } ;
struct brcmf_chip {int dummy; } ;
typedef  int /*<<< orphan*/  rstvec ;
struct TYPE_2__ {struct brcmf_core* sdio_core; } ;

/* Variables and functions */
 scalar_t__ SD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdiod_ramrw (struct brcmf_sdio_dev*,int,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  brcmf_sdiod_writel (struct brcmf_sdio_dev*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intstatus ; 

__attribute__((used)) static void brcmf_sdio_buscore_activate(void *ctx, struct brcmf_chip *chip,
					u32 rstvec)
{
	struct brcmf_sdio_dev *sdiodev = ctx;
	struct brcmf_core *core = sdiodev->bus->sdio_core;
	u32 reg_addr;

	/* clear all interrupts */
	reg_addr = core->base + SD_REG(intstatus);
	brcmf_sdiod_writel(sdiodev, reg_addr, 0xFFFFFFFF, NULL);

	if (rstvec)
		/* Write reset vector to address 0 */
		brcmf_sdiod_ramrw(sdiodev, true, 0, (void *)&rstvec,
				  sizeof(rstvec));
}