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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int mac_len; } ;
struct scatterlist {int dummy; } ;
struct mac802154_llsec_key {int /*<<< orphan*/  tfm0; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwaddr; } ;
struct mac802154_llsec {TYPE_1__ params; } ;
struct ieee802154_hdr {int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llsec_geniv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,unsigned char*,int) ; 
 unsigned char* skb_mac_header (struct sk_buff*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
llsec_do_encrypt_unauth(struct sk_buff *skb, const struct mac802154_llsec *sec,
			const struct ieee802154_hdr *hdr,
			struct mac802154_llsec_key *key)
{
	u8 iv[16];
	struct scatterlist src;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, key->tfm0);
	int err, datalen;
	unsigned char *data;

	llsec_geniv(iv, sec->params.hwaddr, &hdr->sec);
	/* Compute data payload offset and data length */
	data = skb_mac_header(skb) + skb->mac_len;
	datalen = skb_tail_pointer(skb) - data;
	sg_init_one(&src, data, datalen);

	skcipher_request_set_sync_tfm(req, key->tfm0);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, &src, &src, datalen, iv);
	err = crypto_skcipher_encrypt(req);
	skcipher_request_zero(req);
	return err;
}