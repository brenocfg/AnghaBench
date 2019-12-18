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
typedef  int /*<<< orphan*/  u64 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct inode {struct fscrypt_info* i_crypt_info; } ;
struct fscrypt_info {struct crypto_skcipher* ci_ctfm; } ;
struct crypto_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ fscrypt_direction_t ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int /*<<< orphan*/  DECLARE_CRYPTO_WAIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int FS_CRYPTO_BLOCK_SIZE ; 
 scalar_t__ FS_DECRYPT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int /*<<< orphan*/  crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int crypto_wait_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_err (struct inode const*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fscrypt_generate_iv (union fscrypt_iv*,int /*<<< orphan*/ ,struct fscrypt_info*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,unsigned int,unsigned int) ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,union fscrypt_iv*) ; 
 int /*<<< orphan*/  wait ; 

int fscrypt_crypt_block(const struct inode *inode, fscrypt_direction_t rw,
			u64 lblk_num, struct page *src_page,
			struct page *dest_page, unsigned int len,
			unsigned int offs, gfp_t gfp_flags)
{
	union fscrypt_iv iv;
	struct skcipher_request *req = NULL;
	DECLARE_CRYPTO_WAIT(wait);
	struct scatterlist dst, src;
	struct fscrypt_info *ci = inode->i_crypt_info;
	struct crypto_skcipher *tfm = ci->ci_ctfm;
	int res = 0;

	if (WARN_ON_ONCE(len <= 0))
		return -EINVAL;
	if (WARN_ON_ONCE(len % FS_CRYPTO_BLOCK_SIZE != 0))
		return -EINVAL;

	fscrypt_generate_iv(&iv, lblk_num, ci);

	req = skcipher_request_alloc(tfm, gfp_flags);
	if (!req)
		return -ENOMEM;

	skcipher_request_set_callback(
		req, CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
		crypto_req_done, &wait);

	sg_init_table(&dst, 1);
	sg_set_page(&dst, dest_page, len, offs);
	sg_init_table(&src, 1);
	sg_set_page(&src, src_page, len, offs);
	skcipher_request_set_crypt(req, &src, &dst, len, &iv);
	if (rw == FS_DECRYPT)
		res = crypto_wait_req(crypto_skcipher_decrypt(req), &wait);
	else
		res = crypto_wait_req(crypto_skcipher_encrypt(req), &wait);
	skcipher_request_free(req);
	if (res) {
		fscrypt_err(inode, "%scryption failed for block %llu: %d",
			    (rw == FS_DECRYPT ? "De" : "En"), lblk_num, res);
		return res;
	}
	return 0;
}