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
struct ipw_priv {int status; } ;

/* Variables and functions */
 int STATUS_RF_KILL_MASK ; 
 int /*<<< orphan*/  ipw_led_activity_off (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_link_off (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_radio_off (struct ipw_priv*) ; 

__attribute__((used)) static void ipw_led_link_down(struct ipw_priv *priv)
{
	ipw_led_activity_off(priv);
	ipw_led_link_off(priv);

	if (priv->status & STATUS_RF_KILL_MASK)
		ipw_led_radio_off(priv);
}