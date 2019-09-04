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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; void* hw_value; void* center_freq; } ;
struct TYPE_3__ {void* len; void* type; } ;
struct qlink_tlv_channel {TYPE_2__ chan; TYPE_1__ hdr; } ;
struct ieee80211_channel {int center_freq; int hw_value; int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  QLINK_CHAN_NO_IR ; 
 int /*<<< orphan*/  QLINK_CHAN_RADAR ; 
 int QTN_TLV_ID_CHANNEL ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct qlink_tlv_channel* skb_put_zero (struct sk_buff*,int) ; 

__attribute__((used)) static void qtnf_cmd_channel_tlv_add(struct sk_buff *cmd_skb,
				     const struct ieee80211_channel *sc)
{
	struct qlink_tlv_channel *qchan;
	u32 flags = 0;

	qchan = skb_put_zero(cmd_skb, sizeof(*qchan));
	qchan->hdr.type = cpu_to_le16(QTN_TLV_ID_CHANNEL);
	qchan->hdr.len = cpu_to_le16(sizeof(*qchan) - sizeof(qchan->hdr));
	qchan->chan.center_freq = cpu_to_le16(sc->center_freq);
	qchan->chan.hw_value = cpu_to_le16(sc->hw_value);

	if (sc->flags & IEEE80211_CHAN_NO_IR)
		flags |= QLINK_CHAN_NO_IR;

	if (sc->flags & IEEE80211_CHAN_RADAR)
		flags |= QLINK_CHAN_RADAR;

	qchan->chan.flags = cpu_to_le32(flags);
}