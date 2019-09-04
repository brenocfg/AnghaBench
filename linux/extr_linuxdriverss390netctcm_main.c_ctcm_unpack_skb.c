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
struct sk_buff {int len; void* ip_summed; int /*<<< orphan*/  protocol; struct net_device* dev; scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  mtu; struct ctcm_priv* ml_priv; } ;
struct ll_header {scalar_t__ type; int length; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct ctcm_priv {TYPE_1__ stats; } ;
struct channel {scalar_t__ protocol; int logflags; struct net_device* netdev; } ;
typedef  int __u16 ;

/* Variables and functions */
 void* CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  CTCM_DBF_DEV_NAME (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 scalar_t__ CTCM_PROTO_S390 ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ETH_P_IP ; 
 int LL_HEADER_LENGTH ; 
 int LOG_FLAG_ILLEGALPKT ; 
 int LOG_FLAG_ILLEGALSIZE ; 
 int LOG_FLAG_NOMEM ; 
 int LOG_FLAG_OVERRUN ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 

void ctcm_unpack_skb(struct channel *ch, struct sk_buff *pskb)
{
	struct net_device *dev = ch->netdev;
	struct ctcm_priv *priv = dev->ml_priv;
	__u16 len = *((__u16 *) pskb->data);

	skb_put(pskb, 2 + LL_HEADER_LENGTH);
	skb_pull(pskb, 2);
	pskb->dev = dev;
	pskb->ip_summed = CHECKSUM_UNNECESSARY;
	while (len > 0) {
		struct sk_buff *skb;
		int skblen;
		struct ll_header *header = (struct ll_header *)pskb->data;

		skb_pull(pskb, LL_HEADER_LENGTH);
		if ((ch->protocol == CTCM_PROTO_S390) &&
		    (header->type != ETH_P_IP)) {
			if (!(ch->logflags & LOG_FLAG_ILLEGALPKT)) {
				ch->logflags |= LOG_FLAG_ILLEGALPKT;
				/*
				 * Check packet type only if we stick strictly
				 * to S/390's protocol of OS390. This only
				 * supports IP. Otherwise allow any packet
				 * type.
				 */
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): Illegal packet type 0x%04x"
					" - dropping",
					CTCM_FUNTAIL, dev->name, header->type);
			}
			priv->stats.rx_dropped++;
			priv->stats.rx_frame_errors++;
			return;
		}
		pskb->protocol = cpu_to_be16(header->type);
		if ((header->length <= LL_HEADER_LENGTH) ||
		    (len <= LL_HEADER_LENGTH)) {
			if (!(ch->logflags & LOG_FLAG_ILLEGALSIZE)) {
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): Illegal packet size %d(%d,%d)"
					"- dropping",
					CTCM_FUNTAIL, dev->name,
					header->length, dev->mtu, len);
				ch->logflags |= LOG_FLAG_ILLEGALSIZE;
			}

			priv->stats.rx_dropped++;
			priv->stats.rx_length_errors++;
			return;
		}
		header->length -= LL_HEADER_LENGTH;
		len -= LL_HEADER_LENGTH;
		if ((header->length > skb_tailroom(pskb)) ||
		    (header->length > len)) {
			if (!(ch->logflags & LOG_FLAG_OVERRUN)) {
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): Packet size %d (overrun)"
					" - dropping", CTCM_FUNTAIL,
						dev->name, header->length);
				ch->logflags |= LOG_FLAG_OVERRUN;
			}

			priv->stats.rx_dropped++;
			priv->stats.rx_length_errors++;
			return;
		}
		skb_put(pskb, header->length);
		skb_reset_mac_header(pskb);
		len -= header->length;
		skb = dev_alloc_skb(pskb->len);
		if (!skb) {
			if (!(ch->logflags & LOG_FLAG_NOMEM)) {
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): MEMORY allocation error",
						CTCM_FUNTAIL, dev->name);
				ch->logflags |= LOG_FLAG_NOMEM;
			}
			priv->stats.rx_dropped++;
			return;
		}
		skb_copy_from_linear_data(pskb, skb_put(skb, pskb->len),
					  pskb->len);
		skb_reset_mac_header(skb);
		skb->dev = pskb->dev;
		skb->protocol = pskb->protocol;
		pskb->ip_summed = CHECKSUM_UNNECESSARY;
		skblen = skb->len;
		/*
		 * reset logflags
		 */
		ch->logflags = 0;
		priv->stats.rx_packets++;
		priv->stats.rx_bytes += skblen;
		netif_rx_ni(skb);
		if (len > 0) {
			skb_pull(pskb, header->length);
			if (skb_tailroom(pskb) < LL_HEADER_LENGTH) {
				CTCM_DBF_DEV_NAME(TRACE, dev,
					"Overrun in ctcm_unpack_skb");
				ch->logflags |= LOG_FLAG_OVERRUN;
				return;
			}
			skb_put(pskb, LL_HEADER_LENGTH);
		}
	}
}