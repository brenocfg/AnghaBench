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
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; TYPE_1__* i_crypt_info; } ;
struct fscrypt_str {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {struct crypto_skcipher* ci_ctfm; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int FS_CRYPTO_BLOCK_SIZE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int /*<<< orphan*/  crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int fname_decrypt(struct inode *inode,
				const struct fscrypt_str *iname,
				struct fscrypt_str *oname)
{
	struct skcipher_request *req = NULL;
	DECLARE_CRYPTO_WAIT(wait);
	struct scatterlist src_sg, dst_sg;
	struct crypto_skcipher *tfm = inode->i_crypt_info->ci_ctfm;
	int res = 0;
	char iv[FS_CRYPTO_BLOCK_SIZE];

	/* Allocate request */
	req = skcipher_request_alloc(tfm, GFP_NOFS);
	if (!req)
		return -ENOMEM;
	skcipher_request_set_callback(req,
		CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
		crypto_req_done, &wait);

	/* Initialize IV */
	memset(iv, 0, FS_CRYPTO_BLOCK_SIZE);

	/* Create decryption request */
	sg_init_one(&src_sg, iname->name, iname->len);
	sg_init_one(&dst_sg, oname->name, oname->len);
	skcipher_request_set_crypt(req, &src_sg, &dst_sg, iname->len, iv);
	res = crypto_wait_req(crypto_skcipher_decrypt(req), &wait);
	skcipher_request_free(req);
	if (res < 0) {
		fscrypt_err(inode->i_sb,
			    "Filename decryption failed for inode %lu: %d",
			    inode->i_ino, res);
		return res;
	}

	oname->len = strnlen(oname->name, iname->len);
	return 0;
}