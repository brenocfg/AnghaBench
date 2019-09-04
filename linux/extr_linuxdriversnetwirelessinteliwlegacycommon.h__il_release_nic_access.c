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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  _il_clear_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 

__attribute__((used)) static inline void
_il_release_nic_access(struct il_priv *il)
{
	_il_clear_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	/*
	 * In above we are reading CSR_GP_CNTRL register, what will flush any
	 * previous writes, but still want write, which clear MAC_ACCESS_REQ
	 * bit, be performed on PCI bus before any other writes scheduled on
	 * different CPUs (after we drop reg_lock).
	 */
	mmiowb();
}