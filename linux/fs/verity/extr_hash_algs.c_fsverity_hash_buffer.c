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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct fsverity_hash_alg {int /*<<< orphan*/  tfm; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ahash_request* ahash_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  crypto_ahash_digest (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void const*,size_t) ; 
 int /*<<< orphan*/  wait ; 

int fsverity_hash_buffer(const struct fsverity_hash_alg *alg,
			 const void *data, size_t size, u8 *out)
{
	struct ahash_request *req;
	struct scatterlist sg;
	DECLARE_CRYPTO_WAIT(wait);
	int err;

	req = ahash_request_alloc(alg->tfm, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	sg_init_one(&sg, data, size);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_SLEEP |
					CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_done, &wait);
	ahash_request_set_crypt(req, &sg, out, size);

	err = crypto_wait_req(crypto_ahash_digest(req), &wait);

	ahash_request_free(req);
	return err;
}