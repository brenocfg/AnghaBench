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
struct il_priv {int hw_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_PREPARE ; 
 int ETIMEDOUT ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il4965_set_hw_ready (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_prepare_card_hw(struct il_priv *il)
{
	int ret;

	il->hw_ready = false;

	il4965_set_hw_ready(il);
	if (il->hw_ready)
		return;

	/* If HW is not ready, prepare the conditions to check again */
	il_set_bit(il, CSR_HW_IF_CONFIG_REG, CSR_HW_IF_CONFIG_REG_PREPARE);

	ret =
	    _il_poll_bit(il, CSR_HW_IF_CONFIG_REG,
			 ~CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE,
			 CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE, 150000);

	/* HW should be ready by now, check again. */
	if (ret != -ETIMEDOUT)
		il4965_set_hw_ready(il);
}