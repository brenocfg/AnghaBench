#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct brcm_usb_init_params {scalar_t__ selected_family; int product_id; } ;

/* Variables and functions */
 scalar_t__ BRCM_FAMILY_7445D0 ; 
 int /*<<< orphan*/  SCB2_EN ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  USB_CTRL_UNSET_FAMILY (struct brcm_usb_init_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmusb_memc_fix(struct brcm_usb_init_params *params)
{
	u32 prid;

	if (params->selected_family != BRCM_FAMILY_7445D0)
		return;
	/*
	 * This is a workaround for HW7445-1869 where a DMA write ends up
	 * doing a read pre-fetch after the end of the DMA buffer. This
	 * causes a problem when the DMA buffer is at the end of physical
	 * memory, causing the pre-fetch read to access non-existent memory,
	 * and the chip bondout has MEMC2 disabled. When the pre-fetch read
	 * tries to use the disabled MEMC2, it hangs the bus. The workaround
	 * is to disable MEMC2 access in the usb controller which avoids
	 * the hang.
	 */

	prid = params->product_id & 0xfffff000;
	switch (prid) {
	case 0x72520000:
	case 0x74480000:
	case 0x74490000:
	case 0x07252000:
	case 0x07448000:
	case 0x07449000:
		USB_CTRL_UNSET_FAMILY(params, SETUP, SCB2_EN);
	}
}