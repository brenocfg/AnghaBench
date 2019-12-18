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
struct scatterlist {int /*<<< orphan*/  length; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,struct scatterlist*,struct scatterlist*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,struct crypto_aead*) ; 
 size_t crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_decrypt (struct aead_request*) ; 
 int crypto_aead_reqsize (struct crypto_aead*) ; 
 struct aead_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 

int aead_decrypt(struct crypto_aead *tfm, u8 *b_0, u8 *aad, size_t aad_len,
		 u8 *data, size_t data_len, u8 *mic)
{
	size_t mic_len = crypto_aead_authsize(tfm);
	struct scatterlist sg[3];
	struct aead_request *aead_req;
	int reqsize = sizeof(*aead_req) + crypto_aead_reqsize(tfm);
	u8 *__aad;
	int err;

	if (data_len == 0)
		return -EINVAL;

	aead_req = kzalloc(reqsize + aad_len, GFP_ATOMIC);
	if (!aead_req)
		return -ENOMEM;

	__aad = (u8 *)aead_req + reqsize;
	memcpy(__aad, aad, aad_len);

	sg_init_table(sg, 3);
	sg_set_buf(&sg[0], __aad, aad_len);
	sg_set_buf(&sg[1], data, data_len);
	sg_set_buf(&sg[2], mic, mic_len);

	aead_request_set_tfm(aead_req, tfm);
	aead_request_set_crypt(aead_req, sg, sg, data_len + mic_len, b_0);
	aead_request_set_ad(aead_req, sg[0].length);

	err = crypto_aead_decrypt(aead_req);
	kzfree(aead_req);

	return err;
}