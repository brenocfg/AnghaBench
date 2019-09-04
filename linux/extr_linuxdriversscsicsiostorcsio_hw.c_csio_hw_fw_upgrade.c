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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct fw_hdr {int /*<<< orphan*/  flags; } ;
struct csio_hw {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int FW_HDR_FLAGS_RESET_HALT ; 
 int csio_hw_fw_dload (struct csio_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int csio_hw_fw_halt (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int csio_hw_fw_restart (struct csio_hw*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_hw_fw_upgrade(struct csio_hw *hw, uint32_t mbox,
		  const u8 *fw_data, uint32_t size, int32_t force)
{
	const struct fw_hdr *fw_hdr = (const struct fw_hdr *)fw_data;
	int reset, ret;

	ret = csio_hw_fw_halt(hw, mbox, force);
	if (ret != 0 && !force)
		return ret;

	ret = csio_hw_fw_dload(hw, (uint8_t *) fw_data, size);
	if (ret != 0)
		return ret;

	/*
	 * Older versions of the firmware don't understand the new
	 * PCIE_FW.HALT flag and so won't know to perform a RESET when they
	 * restart.  So for newly loaded older firmware we'll have to do the
	 * RESET for it so it starts up on a clean slate.  We can tell if
	 * the newly loaded firmware will handle this right by checking
	 * its header flags to see if it advertises the capability.
	 */
	reset = ((ntohl(fw_hdr->flags) & FW_HDR_FLAGS_RESET_HALT) == 0);
	return csio_hw_fw_restart(hw, mbox, reset);
}