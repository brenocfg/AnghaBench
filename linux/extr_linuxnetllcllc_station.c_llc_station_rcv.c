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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ llc_stat_ev_rx_null_dsap_test_c (struct sk_buff*) ; 
 scalar_t__ llc_stat_ev_rx_null_dsap_xid_c (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_station_ac_send_test_r (struct sk_buff*) ; 
 int /*<<< orphan*/  llc_station_ac_send_xid_r (struct sk_buff*) ; 

__attribute__((used)) static void llc_station_rcv(struct sk_buff *skb)
{
	if (llc_stat_ev_rx_null_dsap_xid_c(skb))
		llc_station_ac_send_xid_r(skb);
	else if (llc_stat_ev_rx_null_dsap_test_c(skb))
		llc_station_ac_send_test_r(skb);
	kfree_skb(skb);
}