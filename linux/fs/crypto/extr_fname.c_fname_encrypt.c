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
typedef  union fscrypt_iv {int dummy; } fscrypt_iv ;
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct qstr {unsigned int len; int /*<<< orphan*/  name; } ;
struct inode {struct fscrypt_info* i_crypt_info; } ;
struct fscrypt_info {struct crypto_skcipher* ci_ctfm; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_err (struct inode*,char*,int) ; 
 int /*<<< orphan*/  fscrypt_generate_iv (union fscrypt_iv*,int /*<<< orphan*/ ,struct fscrypt_info*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,union fscrypt_iv*) ; 
 int /*<<< orphan*/  wait ; 

int fname_encrypt(struct inode *inode, const struct qstr *iname,
		  u8 *out, unsigned int olen)
{
	struct skcipher_request *req = NULL;
	DECLARE_CRYPTO_WAIT(wait);
	struct fscrypt_info *ci = inode->i_crypt_info;
	struct crypto_skcipher *tfm = ci->ci_ctfm;
	union fscrypt_iv iv;
	struct scatterlist sg;
	int res;

	/*
	 * Copy the filename to the output buffer for encrypting in-place and
	 * pad it with the needed number of NUL bytes.
	 */
	if (WARN_ON(olen < iname->len))
		return -ENOBUFS;
	memcpy(out, iname->name, iname->len);
	memset(out + iname->len, 0, olen - iname->len);

	/* Initialize the IV */
	fscrypt_generate_iv(&iv, 0, ci);

	/* Set up the encryption request */
	req = skcipher_request_alloc(tfm, GFP_NOFS);
	if (!req)
		return -ENOMEM;
	skcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			crypto_req_done, &wait);
	sg_init_one(&sg, out, olen);
	skcipher_request_set_crypt(req, &sg, &sg, olen, &iv);

	/* Do the encryption */
	res = crypto_wait_req(crypto_skcipher_encrypt(req), &wait);
	skcipher_request_free(req);
	if (res < 0) {
		fscrypt_err(inode, "Filename encryption failed: %d", res);
		return res;
	}

	return 0;
}