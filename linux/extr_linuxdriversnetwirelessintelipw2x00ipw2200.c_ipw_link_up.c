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
struct ipw_priv {int last_seq_num; int last_frag_num; int config; int /*<<< orphan*/  request_scan; int /*<<< orphan*/  last_rate; int /*<<< orphan*/  scan_event; int /*<<< orphan*/  request_passive_scan; int /*<<< orphan*/  request_direct_scan; int /*<<< orphan*/  net_dev; scalar_t__ last_packet_time; } ;

/* Variables and functions */
 int CFG_BACKGROUND_SCAN ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_gather_stats (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_get_current_rate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_link_up (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_reset_stats (struct ipw_priv*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct ipw_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_link_up(struct ipw_priv *priv)
{
	priv->last_seq_num = -1;
	priv->last_frag_num = -1;
	priv->last_packet_time = 0;

	netif_carrier_on(priv->net_dev);

	cancel_delayed_work(&priv->request_scan);
	cancel_delayed_work(&priv->request_direct_scan);
	cancel_delayed_work(&priv->request_passive_scan);
	cancel_delayed_work(&priv->scan_event);
	ipw_reset_stats(priv);
	/* Ensure the rate is updated immediately */
	priv->last_rate = ipw_get_current_rate(priv);
	ipw_gather_stats(priv);
	ipw_led_link_up(priv);
	notify_wx_assoc_event(priv);

	if (priv->config & CFG_BACKGROUND_SCAN)
		schedule_delayed_work(&priv->request_scan, HZ);
}