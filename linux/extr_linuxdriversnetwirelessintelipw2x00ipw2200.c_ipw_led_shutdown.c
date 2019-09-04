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
struct ipw_priv {int /*<<< orphan*/  led_act_off; int /*<<< orphan*/  led_link_off; int /*<<< orphan*/  led_link_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_led_activity_off (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_band_off (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_link_off (struct ipw_priv*) ; 

__attribute__((used)) static void ipw_led_shutdown(struct ipw_priv *priv)
{
	ipw_led_activity_off(priv);
	ipw_led_link_off(priv);
	ipw_led_band_off(priv);
	cancel_delayed_work(&priv->led_link_on);
	cancel_delayed_work(&priv->led_link_off);
	cancel_delayed_work(&priv->led_act_off);
}