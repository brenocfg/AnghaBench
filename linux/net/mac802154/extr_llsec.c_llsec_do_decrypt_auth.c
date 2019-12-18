#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int mac_len; scalar_t__ len; } ;
struct scatterlist {int dummy; } ;
struct mac802154_llsec_key {int dummy; } ;
struct mac802154_llsec {int dummy; } ;
struct TYPE_3__ {int level; } ;
struct ieee802154_hdr {TYPE_1__ sec; } ;
struct aead_request {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE802154_SCF_SECLEVEL_ENC ; 
 struct aead_request* aead_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ *) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int ieee802154_sechdr_authtag_len (TYPE_1__*) ; 
 int /*<<< orphan*/  kzfree (struct aead_request*) ; 
 int /*<<< orphan*/  llsec_geniv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  llsec_tfm_by_len (struct mac802154_llsec_key*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,unsigned char*,int) ; 
 unsigned char* skb_mac_header (struct sk_buff*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int
llsec_do_decrypt_auth(struct sk_buff *skb, const struct mac802154_llsec *sec,
		      const struct ieee802154_hdr *hdr,
		      struct mac802154_llsec_key *key, __le64 dev_addr)
{
	u8 iv[16];
	unsigned char *data;
	int authlen, datalen, assoclen, rc;
	struct scatterlist sg;
	struct aead_request *req;

	authlen = ieee802154_sechdr_authtag_len(&hdr->sec);
	llsec_geniv(iv, dev_addr, &hdr->sec);

	req = aead_request_alloc(llsec_tfm_by_len(key, authlen), GFP_ATOMIC);
	if (!req)
		return -ENOMEM;

	assoclen = skb->mac_len;

	data = skb_mac_header(skb) + skb->mac_len;
	datalen = skb_tail_pointer(skb) - data;

	sg_init_one(&sg, skb_mac_header(skb), assoclen + datalen);

	if (!(hdr->sec.level & IEEE802154_SCF_SECLEVEL_ENC)) {
		assoclen += datalen - authlen;
		datalen = authlen;
	}

	aead_request_set_callback(req, 0, NULL, NULL);
	aead_request_set_crypt(req, &sg, &sg, datalen, iv);
	aead_request_set_ad(req, assoclen);

	rc = crypto_aead_decrypt(req);

	kzfree(req);
	skb_trim(skb, skb->len - authlen);

	return rc;
}