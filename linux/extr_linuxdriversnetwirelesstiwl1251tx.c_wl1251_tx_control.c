#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int rate_policy; int ack_policy; int tx_complete; int qos; scalar_t__ packet_type; } ;
struct tx_double_buffer_desc {TYPE_1__ control; } ;
struct ieee80211_tx_info {int flags; } ;

/* Variables and functions */
 int IEEE80211_FTYPE_DATA ; 
 int IEEE80211_STYPE_QOS_DATA ; 
 int IEEE80211_STYPE_QOS_NULLFUNC ; 
 int IEEE80211_TX_CTL_INJECTED ; 
 int IEEE80211_TX_CTL_NO_ACK ; 

__attribute__((used)) static void wl1251_tx_control(struct tx_double_buffer_desc *tx_hdr,
			      struct ieee80211_tx_info *control, u16 fc)
{
	*(u16 *)&tx_hdr->control = 0;

	tx_hdr->control.rate_policy = 0;

	/* 802.11 packets */
	tx_hdr->control.packet_type = 0;

	/* Also disable retry and ACK policy for injected packets */
	if ((control->flags & IEEE80211_TX_CTL_NO_ACK) ||
	    (control->flags & IEEE80211_TX_CTL_INJECTED)) {
		tx_hdr->control.rate_policy = 1;
		tx_hdr->control.ack_policy = 1;
	}

	tx_hdr->control.tx_complete = 1;

	if ((fc & IEEE80211_FTYPE_DATA) &&
	    ((fc & IEEE80211_STYPE_QOS_DATA) ||
	     (fc & IEEE80211_STYPE_QOS_NULLFUNC)))
		tx_hdr->control.qos = 1;
}