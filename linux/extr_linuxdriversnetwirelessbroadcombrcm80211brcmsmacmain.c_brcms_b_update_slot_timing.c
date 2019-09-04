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
struct brcms_hardware {struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APHY_SLOT_TIME ; 
 int /*<<< orphan*/  BPHY_SLOT_TIME ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DOT11_SLOT ; 
 int /*<<< orphan*/  bcma_write16 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifs_slot ; 

__attribute__((used)) static void brcms_b_update_slot_timing(struct brcms_hardware *wlc_hw,
					bool shortslot)
{
	struct bcma_device *core = wlc_hw->d11core;

	if (shortslot) {
		/* 11g short slot: 11a timing */
		bcma_write16(core, D11REGOFFS(ifs_slot), 0x0207);
		brcms_b_write_shm(wlc_hw, M_DOT11_SLOT, APHY_SLOT_TIME);
	} else {
		/* 11g long slot: 11b timing */
		bcma_write16(core, D11REGOFFS(ifs_slot), 0x0212);
		brcms_b_write_shm(wlc_hw, M_DOT11_SLOT, BPHY_SLOT_TIME);
	}
}