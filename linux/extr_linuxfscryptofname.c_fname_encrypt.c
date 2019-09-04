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
typedef  char u8 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct qstr {unsigned int len; int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; TYPE_1__* i_crypt_info; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {struct crypto_skcipher* ci_ctfm; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int FS_CRYPTO_BLOCK_SIZE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,char*,unsigned int) ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,char*) ; 
 int /*<<< orphan*/  wait ; 

int fname_encrypt(struct inode *inode, const struct qstr *iname,
		  u8 *out, unsigned int olen)
{
	struct skcipher_request *req = NULL;
	DECLARE_CRYPTO_WAIT(wait);
	struct crypto_skcipher *tfm = inode->i_crypt_info->ci_ctfm;
	int res = 0;
	char iv[FS_CRYPTO_BLOCK_SIZE];
	struct scatterlist sg;

	/*
	 * Copy the filename to the output buffer for encrypting in-place and
	 * pad it with the needed number of NUL bytes.
	 */
	if (WARN_ON(olen < iname->len))
		return -ENOBUFS;
	memcpy(out, iname->name, iname->len);
	memset(out + iname->len, 0, olen - iname->len);

	/* Initialize the IV */
	memset(iv, 0, FS_CRYPTO_BLOCK_SIZE);

	/* Set up the encryption request */
	req = skcipher_request_alloc(tfm, GFP_NOFS);
	if (!req)
		return -ENOMEM;
	skcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			crypto_req_done, &wait);
	sg_init_one(&sg, out, olen);
	skcipher_request_set_crypt(req, &sg, &sg, olen, iv);

	/* Do the encryption */
	res = crypto_wait_req(crypto_skcipher_encrypt(req), &wait);
	skcipher_request_free(req);
	if (res < 0) {
		fscrypt_err(inode->i_sb,
			    "Filename encryption failed for inode %lu: %d",
			    inode->i_ino, res);
		return res;
	}

	return 0;
}