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
struct vnt_usb_send_context {TYPE_1__* skb; } ;
struct ieee80211_rts {int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  duration; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_STYPE_RTS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnt_fill_ieee80211_rts(struct vnt_usb_send_context *tx_context,
				  struct ieee80211_rts *rts, __le16 duration)
{
	struct ieee80211_hdr *hdr =
				(struct ieee80211_hdr *)tx_context->skb->data;

	rts->duration = duration;
	rts->frame_control =
		cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_RTS);

	ether_addr_copy(rts->ra, hdr->addr1);
	ether_addr_copy(rts->ta, hdr->addr2);

	return 0;
}