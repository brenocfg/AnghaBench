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
typedef  int u32 ;
struct brcmf_sdio_dev {TYPE_1__* func1; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int BRCM_CC_4339_CHIP_ID ; 
 int CID_ID_MASK ; 
 int CID_REV_MASK ; 
 int CID_REV_SHIFT ; 
 int CORE_CC_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SDIO_DEVICE_ID_BROADCOM_4335_4339 ; 
 scalar_t__ SDIO_DEVICE_ID_BROADCOM_4339 ; 
 int /*<<< orphan*/  SI_ENUM_BASE ; 
 int brcmf_sdiod_readl (struct brcmf_sdio_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chipid ; 

__attribute__((used)) static u32 brcmf_sdio_buscore_read32(void *ctx, u32 addr)
{
	struct brcmf_sdio_dev *sdiodev = ctx;
	u32 val, rev;

	val = brcmf_sdiod_readl(sdiodev, addr, NULL);

	/*
	 * this is a bit of special handling if reading the chipcommon chipid
	 * register. The 4339 is a next-gen of the 4335. It uses the same
	 * SDIO device id as 4335 and the chipid register returns 4335 as well.
	 * It can be identified as 4339 by looking at the chip revision. It
	 * is corrected here so the chip.c module has the right info.
	 */
	if (addr == CORE_CC_REG(SI_ENUM_BASE, chipid) &&
	    (sdiodev->func1->device == SDIO_DEVICE_ID_BROADCOM_4339 ||
	     sdiodev->func1->device == SDIO_DEVICE_ID_BROADCOM_4335_4339)) {
		rev = (val & CID_REV_MASK) >> CID_REV_SHIFT;
		if (rev >= 2) {
			val &= ~CID_ID_MASK;
			val |= BRCM_CC_4339_CHIP_ID;
		}
	}

	return val;
}