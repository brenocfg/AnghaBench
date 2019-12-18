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
typedef  int u8 ;
struct sk_buff {int len; int* data; } ;
struct scatterlist {int dummy; } ;
struct lib80211_ccmp_data {int* rx_aad; int key_idx; int /*<<< orphan*/ * rx_pn; int /*<<< orphan*/  dot11RSNAStatsCCMPDecryptErrors; int /*<<< orphan*/  tfm; int /*<<< orphan*/  dot11RSNAStatsCCMPReplays; int /*<<< orphan*/  key_set; int /*<<< orphan*/  dot11RSNAStatsCCMPFormatErrors; } ;
struct ieee80211_hdr {int addr2; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 int CCMP_HDR_LEN ; 
 int CCMP_MIC_LEN ; 
 int /*<<< orphan*/  CCMP_PN_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct aead_request* aead_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_free (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,size_t,int*) ; 
 int ccmp_init_iv_and_aad (struct ieee80211_hdr*,int*,int*,int*) ; 
 scalar_t__ ccmp_replay_check (int*,int /*<<< orphan*/ *) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int,...) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int*,size_t) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int lib80211_ccmp_decrypt(struct sk_buff *skb, int hdr_len, void *priv)
{
	struct lib80211_ccmp_data *key = priv;
	u8 keyidx, *pos;
	struct ieee80211_hdr *hdr;
	struct aead_request *req;
	struct scatterlist sg[2];
	u8 *aad = key->rx_aad;
	u8 iv[AES_BLOCK_LEN];
	u8 pn[6];
	int aad_len, ret;
	size_t data_len = skb->len - hdr_len - CCMP_HDR_LEN;

	if (skb->len < hdr_len + CCMP_HDR_LEN + CCMP_MIC_LEN) {
		key->dot11RSNAStatsCCMPFormatErrors++;
		return -1;
	}

	hdr = (struct ieee80211_hdr *)skb->data;
	pos = skb->data + hdr_len;
	keyidx = pos[3];
	if (!(keyidx & (1 << 5))) {
		net_dbg_ratelimited("CCMP: received packet without ExtIV flag from %pM\n",
				    hdr->addr2);
		key->dot11RSNAStatsCCMPFormatErrors++;
		return -2;
	}
	keyidx >>= 6;
	if (key->key_idx != keyidx) {
		net_dbg_ratelimited("CCMP: RX tkey->key_idx=%d frame keyidx=%d\n",
				    key->key_idx, keyidx);
		return -6;
	}
	if (!key->key_set) {
		net_dbg_ratelimited("CCMP: received packet from %pM with keyid=%d that does not have a configured key\n",
				    hdr->addr2, keyidx);
		return -3;
	}

	pn[0] = pos[7];
	pn[1] = pos[6];
	pn[2] = pos[5];
	pn[3] = pos[4];
	pn[4] = pos[1];
	pn[5] = pos[0];
	pos += 8;

	if (ccmp_replay_check(pn, key->rx_pn)) {
#ifdef CONFIG_LIB80211_DEBUG
		net_dbg_ratelimited("CCMP: replay detected: STA=%pM previous PN %02x%02x%02x%02x%02x%02x received PN %02x%02x%02x%02x%02x%02x\n",
				    hdr->addr2,
				    key->rx_pn[0], key->rx_pn[1], key->rx_pn[2],
				    key->rx_pn[3], key->rx_pn[4], key->rx_pn[5],
				    pn[0], pn[1], pn[2], pn[3], pn[4], pn[5]);
#endif
		key->dot11RSNAStatsCCMPReplays++;
		return -4;
	}

	req = aead_request_alloc(key->tfm, GFP_ATOMIC);
	if (!req)
		return -ENOMEM;

	aad_len = ccmp_init_iv_and_aad(hdr, pn, iv, aad);

	sg_init_table(sg, 2);
	sg_set_buf(&sg[0], aad, aad_len);
	sg_set_buf(&sg[1], pos, data_len);

	aead_request_set_callback(req, 0, NULL, NULL);
	aead_request_set_ad(req, aad_len);
	aead_request_set_crypt(req, sg, sg, data_len, iv);

	ret = crypto_aead_decrypt(req);
	aead_request_free(req);

	if (ret) {
		net_dbg_ratelimited("CCMP: decrypt failed: STA=%pM (%d)\n",
				    hdr->addr2, ret);
		key->dot11RSNAStatsCCMPDecryptErrors++;
		return -5;
	}

	memcpy(key->rx_pn, pn, CCMP_PN_LEN);

	/* Remove hdr and MIC */
	memmove(skb->data + CCMP_HDR_LEN, skb->data, hdr_len);
	skb_pull(skb, CCMP_HDR_LEN);
	skb_trim(skb, skb->len - CCMP_MIC_LEN);

	return keyidx;
}