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
struct ipw_priv {int config; scalar_t__ nic_type; int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  led_link_off; int /*<<< orphan*/  led_association_on; } ;

/* Variables and functions */
 int CFG_NO_LED ; 
 scalar_t__ EEPROM_NIC_TYPE_1 ; 
 int /*<<< orphan*/  IPW_DEBUG_LED (char*,...) ; 
 int /*<<< orphan*/  IPW_EVENT_REG ; 
 int /*<<< orphan*/  LD_TIME_LINK_ON ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_LED_LINK_ON ; 
 int STATUS_RF_KILL_MASK ; 
 int /*<<< orphan*/  ipw_read_reg32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_register_toggle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ipw_led_link_on(struct ipw_priv *priv)
{
	unsigned long flags;
	u32 led;

	/* If configured to not use LEDs, or nic_type is 1,
	 * then we don't toggle a LINK led */
	if (priv->config & CFG_NO_LED || priv->nic_type == EEPROM_NIC_TYPE_1)
		return;

	spin_lock_irqsave(&priv->lock, flags);

	if (!(priv->status & STATUS_RF_KILL_MASK) &&
	    !(priv->status & STATUS_LED_LINK_ON)) {
		IPW_DEBUG_LED("Link LED On\n");
		led = ipw_read_reg32(priv, IPW_EVENT_REG);
		led |= priv->led_association_on;

		led = ipw_register_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_write_reg32(priv, IPW_EVENT_REG, led);

		priv->status |= STATUS_LED_LINK_ON;

		/* If we aren't associated, schedule turning the LED off */
		if (!(priv->status & STATUS_ASSOCIATED))
			schedule_delayed_work(&priv->led_link_off,
					      LD_TIME_LINK_ON);
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}