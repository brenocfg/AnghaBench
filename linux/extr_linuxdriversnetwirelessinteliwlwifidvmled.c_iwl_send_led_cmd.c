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
struct iwl_priv {int /*<<< orphan*/  trans; } ;
struct iwl_led_cmd {int dummy; } ;
struct iwl_host_cmd {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int CSR_LED_BSM_CTRL_MSK ; 
 int /*<<< orphan*/  CSR_LED_REG ; 
 int /*<<< orphan*/  REPLY_LEDS_CMD ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int iwl_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_send_led_cmd(struct iwl_priv *priv, struct iwl_led_cmd *led_cmd)
{
	struct iwl_host_cmd cmd = {
		.id = REPLY_LEDS_CMD,
		.len = { sizeof(struct iwl_led_cmd), },
		.data = { led_cmd, },
		.flags = CMD_ASYNC,
	};
	u32 reg;

	reg = iwl_read32(priv->trans, CSR_LED_REG);
	if (reg != (reg & CSR_LED_BSM_CTRL_MSK))
		iwl_write32(priv->trans, CSR_LED_REG,
			    reg & CSR_LED_BSM_CTRL_MSK);

	return iwl_dvm_send_cmd(priv, &cmd);
}