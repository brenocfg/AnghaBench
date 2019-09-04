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
struct sk_buff {int* data; scalar_t__ cb; } ;
struct rtllib_hdr_4addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_ctl; } ;
struct rtllib_device {int /*<<< orphan*/  dev; scalar_t__ need_sw_enc; scalar_t__ hwsec_active; } ;
struct lib80211_crypt_data {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct cb_desc {int bHwSec; } ;
struct TYPE_2__ {int (* decrypt_mpdu ) (struct sk_buff*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int rtllib_get_hdrlen (int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rtllib_rx_frame_decrypt(struct rtllib_device *ieee, struct sk_buff *skb,
			struct lib80211_crypt_data *crypt)
{
	struct rtllib_hdr_4addr *hdr;
	int res, hdrlen;

	if (crypt == NULL || crypt->ops->decrypt_mpdu == NULL)
		return 0;

	if (ieee->hwsec_active) {
		struct cb_desc *tcb_desc = (struct cb_desc *)
						(skb->cb + MAX_DEV_ADDR_SIZE);

		tcb_desc->bHwSec = 1;

		if (ieee->need_sw_enc)
			tcb_desc->bHwSec = 0;
	}

	hdr = (struct rtllib_hdr_4addr *) skb->data;
	hdrlen = rtllib_get_hdrlen(le16_to_cpu(hdr->frame_ctl));

	atomic_inc(&crypt->refcnt);
	res = crypt->ops->decrypt_mpdu(skb, hdrlen, crypt->priv);
	atomic_dec(&crypt->refcnt);
	if (res < 0) {
		netdev_dbg(ieee->dev, "decryption failed (SA= %pM) res=%d\n",
			   hdr->addr2, res);
		if (res == -2)
			netdev_dbg(ieee->dev,
				   "Decryption failed ICV mismatch (key %d)\n",
				   skb->data[hdrlen + 3] >> 6);
		return -1;
	}

	return res;
}