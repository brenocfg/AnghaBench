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
typedef  int /*<<< orphan*/  zero_nonce ;
typedef  int /*<<< orphan*/  u8 ;
struct big_key_buf {int /*<<< orphan*/  sg; } ;
struct aead_request {int dummy; } ;
typedef  enum big_key_op { ____Placeholder_big_key_op } big_key_op ;

/* Variables and functions */
 int BIG_KEY_ENC ; 
 int BIG_KEY_IV_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EAGAIN ; 
 int /*<<< orphan*/  ENC_KEY_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct aead_request* aead_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_free (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  big_key_aead ; 
 int /*<<< orphan*/  big_key_aead_lock ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 scalar_t__ crypto_aead_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int big_key_crypt(enum big_key_op op, struct big_key_buf *buf, size_t datalen, u8 *key)
{
	int ret;
	struct aead_request *aead_req;
	/* We always use a zero nonce. The reason we can get away with this is
	 * because we're using a different randomly generated key for every
	 * different encryption. Notably, too, key_type_big_key doesn't define
	 * an .update function, so there's no chance we'll wind up reusing the
	 * key to encrypt updated data. Simply put: one key, one encryption.
	 */
	u8 zero_nonce[BIG_KEY_IV_SIZE];

	aead_req = aead_request_alloc(big_key_aead, GFP_KERNEL);
	if (!aead_req)
		return -ENOMEM;

	memset(zero_nonce, 0, sizeof(zero_nonce));
	aead_request_set_crypt(aead_req, buf->sg, buf->sg, datalen, zero_nonce);
	aead_request_set_callback(aead_req, CRYPTO_TFM_REQ_MAY_SLEEP, NULL, NULL);
	aead_request_set_ad(aead_req, 0);

	mutex_lock(&big_key_aead_lock);
	if (crypto_aead_setkey(big_key_aead, key, ENC_KEY_SIZE)) {
		ret = -EAGAIN;
		goto error;
	}
	if (op == BIG_KEY_ENC)
		ret = crypto_aead_encrypt(aead_req);
	else
		ret = crypto_aead_decrypt(aead_req);
error:
	mutex_unlock(&big_key_aead_lock);
	aead_request_free(aead_req);
	return ret;
}