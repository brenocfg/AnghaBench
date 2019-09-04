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
typedef  int /*<<< orphan*/  u32 ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN ; 
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  CSR_RESET_REG_FLAG_FORCE_NMI ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool
_il_grab_nic_access(struct il_priv *il)
{
	int ret;
	u32 val;

	/* this bit wakes up the NIC */
	_il_set_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	/*
	 * These bits say the device is running, and should keep running for
	 * at least a short while (at least as long as MAC_ACCESS_REQ stays 1),
	 * but they do not indicate that embedded SRAM is restored yet;
	 * 3945 and 4965 have volatile SRAM, and must save/restore contents
	 * to/from host DRAM when sleeping/waking for power-saving.
	 * Each direction takes approximately 1/4 millisecond; with this
	 * overhead, it's a good idea to grab and hold MAC_ACCESS_REQUEST if a
	 * series of register accesses are expected (e.g. reading Event Log),
	 * to keep device from sleeping.
	 *
	 * CSR_UCODE_DRV_GP1 register bit MAC_SLEEP == 0 indicates that
	 * SRAM is okay/restored.  We don't check that here because this call
	 * is just for hardware register access; but GP1 MAC_SLEEP check is a
	 * good idea before accessing 3945/4965 SRAM (e.g. reading Event Log).
	 *
	 */
	ret =
	    _il_poll_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN,
			 (CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY |
			  CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP), 15000);
	if (unlikely(ret < 0)) {
		val = _il_rd(il, CSR_GP_CNTRL);
		WARN_ONCE(1, "Timeout waiting for ucode processor access "
			     "(CSR_GP_CNTRL 0x%08x)\n", val);
		_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_FORCE_NMI);
		return false;
	}

	return true;
}