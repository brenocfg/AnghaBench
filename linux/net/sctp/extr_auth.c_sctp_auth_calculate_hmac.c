#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct sctp_shared_key {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hmac; int /*<<< orphan*/  hmac_id; int /*<<< orphan*/  shkey_id; } ;
struct sctp_auth_chunk {TYPE_2__ auth_hdr; } ;
struct sctp_auth_bytes {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct sctp_association {scalar_t__ active_key_id; TYPE_1__* ep; struct sctp_auth_bytes* asoc_shared_key; } ;
struct crypto_shash {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u16 ;
struct TYPE_9__ {struct crypto_shash* tfm; } ;
struct TYPE_7__ {struct crypto_shash** auth_hmacs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_3__*,struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_shash_digest (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* desc ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct sctp_auth_bytes* sctp_auth_asoc_create_secret (struct sctp_association const*,struct sctp_shared_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_key_put (struct sctp_auth_bytes*) ; 
 int /*<<< orphan*/  shash_desc_zero (TYPE_3__*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

void sctp_auth_calculate_hmac(const struct sctp_association *asoc,
			      struct sk_buff *skb, struct sctp_auth_chunk *auth,
			      struct sctp_shared_key *ep_key, gfp_t gfp)
{
	struct sctp_auth_bytes *asoc_key;
	struct crypto_shash *tfm;
	__u16 key_id, hmac_id;
	unsigned char *end;
	int free_key = 0;
	__u8 *digest;

	/* Extract the info we need:
	 * - hmac id
	 * - key id
	 */
	key_id = ntohs(auth->auth_hdr.shkey_id);
	hmac_id = ntohs(auth->auth_hdr.hmac_id);

	if (key_id == asoc->active_key_id)
		asoc_key = asoc->asoc_shared_key;
	else {
		/* ep_key can't be NULL here */
		asoc_key = sctp_auth_asoc_create_secret(asoc, ep_key, gfp);
		if (!asoc_key)
			return;

		free_key = 1;
	}

	/* set up scatter list */
	end = skb_tail_pointer(skb);

	tfm = asoc->ep->auth_hmacs[hmac_id];

	digest = auth->auth_hdr.hmac;
	if (crypto_shash_setkey(tfm, &asoc_key->data[0], asoc_key->len))
		goto free;

	{
		SHASH_DESC_ON_STACK(desc, tfm);

		desc->tfm = tfm;
		crypto_shash_digest(desc, (u8 *)auth,
				    end - (unsigned char *)auth, digest);
		shash_desc_zero(desc);
	}

free:
	if (free_key)
		sctp_auth_key_put(asoc_key);
}