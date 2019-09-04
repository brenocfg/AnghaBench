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
typedef  int u16 ;
struct sk_buff {int* data; size_t len; } ;
struct rtllib_hdr_4addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_ctl; } ;
struct TYPE_3__ {struct lib80211_crypt_data** crypt; } ;
struct rtllib_device {int /*<<< orphan*/  dev; TYPE_1__ crypt_info; scalar_t__ host_decrypt; } ;
struct lib80211_crypt_data {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/ * decrypt_mpdu; } ;

/* Variables and functions */
 int RTLLIB_FCTL_WEP ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtllib_rx_get_crypt(struct rtllib_device *ieee, struct sk_buff *skb,
			struct lib80211_crypt_data **crypt, size_t hdrlen)
{
	struct rtllib_hdr_4addr *hdr = (struct rtllib_hdr_4addr *)skb->data;
	u16 fc = le16_to_cpu(hdr->frame_ctl);
	int idx = 0;

	if (ieee->host_decrypt) {
		if (skb->len >= hdrlen + 3)
			idx = skb->data[hdrlen + 3] >> 6;

		*crypt = ieee->crypt_info.crypt[idx];
		/* allow NULL decrypt to indicate an station specific override
		 * for default encryption
		 */
		if (*crypt && ((*crypt)->ops == NULL ||
			      (*crypt)->ops->decrypt_mpdu == NULL))
			*crypt = NULL;

		if (!*crypt && (fc & RTLLIB_FCTL_WEP)) {
			/* This seems to be triggered by some (multicast?)
			 * frames from other than current BSS, so just drop the
			 * frames silently instead of filling system log with
			 * these reports.
			 */
			netdev_dbg(ieee->dev,
				   "Decryption failed (not set) (SA= %pM)\n",
				   hdr->addr2);
			return -1;
		}
	}

	return 0;
}