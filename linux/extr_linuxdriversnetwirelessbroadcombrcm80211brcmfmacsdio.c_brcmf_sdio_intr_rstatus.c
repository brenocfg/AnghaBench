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
struct TYPE_2__ {int /*<<< orphan*/  f1regdata; } ;
struct brcmf_sdio {unsigned long hostintmask; int /*<<< orphan*/  intstatus; TYPE_1__ sdcnt; int /*<<< orphan*/  sdiodev; int /*<<< orphan*/  fcstate; struct brcmf_core* sdio_core; } ;
struct brcmf_core {scalar_t__ base; } ;

/* Variables and functions */
 unsigned long I_HMB_FC_STATE ; 
 scalar_t__ SD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_or (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 unsigned long brcmf_sdiod_readl (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writel (int /*<<< orphan*/ ,scalar_t__,unsigned long,int*) ; 
 int /*<<< orphan*/  intstatus ; 

__attribute__((used)) static int brcmf_sdio_intr_rstatus(struct brcmf_sdio *bus)
{
	struct brcmf_core *core = bus->sdio_core;
	u32 addr;
	unsigned long val;
	int ret;

	addr = core->base + SD_REG(intstatus);

	val = brcmf_sdiod_readl(bus->sdiodev, addr, &ret);
	bus->sdcnt.f1regdata++;
	if (ret != 0)
		return ret;

	val &= bus->hostintmask;
	atomic_set(&bus->fcstate, !!(val & I_HMB_FC_STATE));

	/* Clear interrupts */
	if (val) {
		brcmf_sdiod_writel(bus->sdiodev, addr, val, &ret);
		bus->sdcnt.f1regdata++;
		atomic_or(val, &bus->intstatus);
	}

	return ret;
}