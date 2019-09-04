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
struct iwl_priv {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_DRIVER_REG ; 
 int /*<<< orphan*/  CSR_GP_DRIVER_REG_BIT_RADIO_IQ_INVER ; 
 int /*<<< orphan*/  iwl_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl2000_nic_config(struct iwl_priv *priv)
{
	iwl_set_bit(priv->trans, CSR_GP_DRIVER_REG,
		    CSR_GP_DRIVER_REG_BIT_RADIO_IQ_INVER);
}