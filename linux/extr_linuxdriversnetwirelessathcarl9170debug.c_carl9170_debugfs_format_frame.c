#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tx_info {scalar_t__ rate_driver_data; } ;
struct ieee80211_hdr {int dummy; } ;
struct carl9170_tx_info {scalar_t__ timeout; } ;
struct ar9170 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_control; int /*<<< orphan*/  mac_control; } ;
struct TYPE_3__ {int /*<<< orphan*/  cookie; } ;
struct _carl9170_tx_superframe {TYPE_2__ f; TYPE_1__ s; scalar_t__ frame_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  get_seq_h (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carl9170_debugfs_format_frame(struct ar9170 *ar,
	struct sk_buff *skb, const char *prefix, char *buf,
	ssize_t *off, ssize_t bufsize)
{
	struct _carl9170_tx_superframe *txc = (void *) skb->data;
	struct ieee80211_tx_info *txinfo = IEEE80211_SKB_CB(skb);
	struct carl9170_tx_info *arinfo = (void *) txinfo->rate_driver_data;
	struct ieee80211_hdr *hdr = (void *) txc->frame_data;

	ADD(buf, *off, bufsize, "%s %p, c:%2x, DA:%pM, sq:%4d, mc:%.4x, "
	    "pc:%.8x, to:%d ms\n", prefix, skb, txc->s.cookie,
	    ieee80211_get_DA(hdr), get_seq_h(hdr),
	    le16_to_cpu(txc->f.mac_control), le32_to_cpu(txc->f.phy_control),
	    jiffies_to_msecs(jiffies - arinfo->timeout));
}