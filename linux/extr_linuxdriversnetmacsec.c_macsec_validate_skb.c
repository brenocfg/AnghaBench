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
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct macsec_eth_header {int tci_an; int short_length; int /*<<< orphan*/  packet_number; scalar_t__ unused; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int MACSEC_TCI_ES ; 
 int MACSEC_TCI_SC ; 
 int MACSEC_TCI_SCB ; 
 int MACSEC_TCI_VERSION ; 
 int MIN_NON_SHORT_LEN ; 
 int macsec_extra_len (int) ; 

__attribute__((used)) static bool macsec_validate_skb(struct sk_buff *skb, u16 icv_len)
{
	struct macsec_eth_header *h = (struct macsec_eth_header *)skb->data;
	int len = skb->len - 2 * ETH_ALEN;
	int extra_len = macsec_extra_len(!!(h->tci_an & MACSEC_TCI_SC)) + icv_len;

	/* a) It comprises at least 17 octets */
	if (skb->len <= 16)
		return false;

	/* b) MACsec EtherType: already checked */

	/* c) V bit is clear */
	if (h->tci_an & MACSEC_TCI_VERSION)
		return false;

	/* d) ES or SCB => !SC */
	if ((h->tci_an & MACSEC_TCI_ES || h->tci_an & MACSEC_TCI_SCB) &&
	    (h->tci_an & MACSEC_TCI_SC))
		return false;

	/* e) Bits 7 and 8 of octet 4 of the SecTAG are clear */
	if (h->unused)
		return false;

	/* rx.pn != 0 (figure 10-5) */
	if (!h->packet_number)
		return false;

	/* length check, f) g) h) i) */
	if (h->short_length)
		return len == extra_len + h->short_length;
	return len >= extra_len + MIN_NON_SHORT_LEN;
}