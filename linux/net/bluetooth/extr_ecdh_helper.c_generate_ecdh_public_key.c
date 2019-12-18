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
 int crypto_kpp_generate_public_key (struct kpp_request*) ; 
 int /*<<< orphan*/  ecdh_complete ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct kpp_request* kpp_request_alloc (struct crypto_kpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpp_request_free (struct kpp_request*) ; 
 int /*<<< orphan*/  kpp_request_set_callback (struct kpp_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecdh_completion*) ; 
 int /*<<< orphan*/  kpp_request_set_input (struct kpp_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpp_request_set_output (struct kpp_request*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swap_digits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int generate_ecdh_public_key(struct crypto_kpp *tfm, u8 public_key[64])
{
	struct kpp_request *req;
	u8 *tmp;
	struct ecdh_completion result;
	struct scatterlist dst;
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
	sg_init_one(&dst, tmp, 64);
	kpp_request_set_input(req, NULL, 0);
	kpp_request_set_output(req, &dst, 64);
	kpp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				 ecdh_complete, &result);

	err = crypto_kpp_generate_public_key(req);
	if (err == -EINPROGRESS) {
		wait_for_completion(&result.completion);
		err = result.err;
	}
	if (err < 0)
		goto free_all;

	/* The public key is handed back in little endian as expected by
	 * the Security Manager Protocol.
	 */
	swap_digits((u64 *)tmp, (u64 *)public_key, 4); /* x */
	swap_digits((u64 *)&tmp[32], (u64 *)&public_key[32], 4); /* y */

free_all:
	kpp_request_free(req);
free_tmp:
	kfree(tmp);
	return err;
}