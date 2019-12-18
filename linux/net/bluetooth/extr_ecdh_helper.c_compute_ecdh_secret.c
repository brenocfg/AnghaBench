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
typedef  int /*<<< orphan*/  u64 ;
struct scatterlist {int dummy; } ;
struct kpp_request {int dummy; } ;
struct ecdh_completion {int err; int /*<<< orphan*/  completion; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int crypto_kpp_compute_shared_secret (struct kpp_request*) ; 
 int /*<<< orphan*/  ecdh_complete ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct kpp_request* kpp_request_alloc (struct crypto_kpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpp_request_free (struct kpp_request*) ; 
 int /*<<< orphan*/  kpp_request_set_callback (struct kpp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecdh_completion*) ; 
 int /*<<< orphan*/  kpp_request_set_input (struct kpp_request*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  kpp_request_set_output (struct kpp_request*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swap_digits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int compute_ecdh_secret(struct crypto_kpp *tfm, const u8 public_key[64],
			u8 secret[32])
{
	struct kpp_request *req;
	u8 *tmp;
	struct ecdh_completion result;
	struct scatterlist src, dst;
	int err;

	tmp = kmalloc(64, GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	req = kpp_request_alloc(tfm, GFP_KERNEL);
	if (!req) {
		err = -ENOMEM;
		goto free_tmp;
	}

	init_completion(&result.completion);

	swap_digits((u64 *)public_key, (u64 *)tmp, 4); /* x */
	swap_digits((u64 *)&public_key[32], (u64 *)&tmp[32], 4); /* y */

	sg_init_one(&src, tmp, 64);
	sg_init_one(&dst, secret, 32);
	kpp_request_set_input(req, &src, 64);
	kpp_request_set_output(req, &dst, 32);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 ecdh_complete, &result);
	err = crypto_kpp_compute_shared_secret(req);
	if (err == -EINPROGRESS) {
		wait_for_completion(&result.completion);
		err = result.err;
	}
	if (err < 0) {
		pr_err("alg: ecdh: compute shared secret failed. err %d\n",
		       err);
		goto free_all;
	}

	swap_digits((u64 *)secret, (u64 *)tmp, 4);
	memcpy(secret, tmp, 32);

free_all:
	kpp_request_free(req);
free_tmp:
	kzfree(tmp);
	return err;
}