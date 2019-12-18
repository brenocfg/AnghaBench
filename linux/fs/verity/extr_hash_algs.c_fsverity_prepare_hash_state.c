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
typedef  int /*<<< orphan*/  const u8 ;
struct scatterlist {int dummy; } ;
struct fsverity_hash_alg {int /*<<< orphan*/  block_size; int /*<<< orphan*/  tfm; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  const* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ahash_request* ahash_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 int crypto_ahash_export (struct ahash_request*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_ahash_init (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_ahash_statesize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 size_t round_up (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wait ; 

const u8 *fsverity_prepare_hash_state(const struct fsverity_hash_alg *alg,
				      const u8 *salt, size_t salt_size)
{
	u8 *hashstate = NULL;
	struct ahash_request *req = NULL;
	u8 *padded_salt = NULL;
	size_t padded_salt_size;
	struct scatterlist sg;
	DECLARE_CRYPTO_WAIT(wait);
	int err;

	if (salt_size == 0)
		return NULL;

	hashstate = kmalloc(crypto_ahash_statesize(alg->tfm), GFP_KERNEL);
	if (!hashstate)
		return ERR_PTR(-ENOMEM);

	req = ahash_request_alloc(alg->tfm, GFP_KERNEL);
	if (!req) {
		err = -ENOMEM;
		goto err_free;
	}

	/*
	 * Zero-pad the salt to the next multiple of the input size of the hash
	 * algorithm's compression function, e.g. 64 bytes for SHA-256 or 128
	 * bytes for SHA-512.  This ensures that the hash algorithm won't have
	 * any bytes buffered internally after processing the salt, thus making
	 * salted hashing just as fast as unsalted hashing.
	 */
	padded_salt_size = round_up(salt_size, alg->block_size);
	padded_salt = kzalloc(padded_salt_size, GFP_KERNEL);
	if (!padded_salt) {
		err = -ENOMEM;
		goto err_free;
	}
	memcpy(padded_salt, salt, salt_size);

	sg_init_one(&sg, padded_salt, padded_salt_size);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_done, &wait);
	ahash_request_set_crypt(req, &sg, NULL, padded_salt_size);

	err = crypto_wait_req(crypto_ahash_init(req), &wait);
	if (err)
		goto err_free;

	err = crypto_wait_req(crypto_ahash_update(req), &wait);
	if (err)
		goto err_free;

	err = crypto_ahash_export(req, hashstate);
	if (err)
		goto err_free;
out:
	ahash_request_free(req);
	kfree(padded_salt);
	return hashstate;

err_free:
	kfree(hashstate);
	hashstate = ERR_PTR(err);
	goto out;
}