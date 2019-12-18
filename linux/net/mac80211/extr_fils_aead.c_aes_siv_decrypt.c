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
typedef  int u8 ;
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
typedef  struct crypto_skcipher crypto_shash ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int PTR_ERR (struct crypto_skcipher*) ; 
 int aes_s2v (struct crypto_skcipher*,size_t,int const**,size_t*,int*) ; 
 struct crypto_skcipher* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_skcipher* crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 int crypto_shash_setkey (struct crypto_skcipher*,int const*,size_t) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_skcipher_setkey (struct crypto_skcipher*,int const*,size_t) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int const*,size_t) ; 
 struct skcipher_request* skcipher_request_alloc (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,size_t,int*) ; 

__attribute__((used)) static int aes_siv_decrypt(const u8 *key, size_t key_len,
			   const u8 *iv_crypt, size_t iv_c_len,
			   size_t num_elem, const u8 *addr[], size_t len[],
			   u8 *out)
{
	struct crypto_shash *tfm;
	struct crypto_skcipher *tfm2;
	struct skcipher_request *req;
	struct scatterlist src[1], dst[1];
	size_t crypt_len;
	int res;
	u8 frame_iv[AES_BLOCK_SIZE], iv[AES_BLOCK_SIZE];
	u8 check[AES_BLOCK_SIZE];

	crypt_len = iv_c_len - AES_BLOCK_SIZE;
	key_len /= 2; /* S2V key || CTR key */
	addr[num_elem] = out;
	len[num_elem] = crypt_len;
	num_elem++;

	memcpy(iv, iv_crypt, AES_BLOCK_SIZE);
	memcpy(frame_iv, iv_crypt, AES_BLOCK_SIZE);

	/* Synthetic IV to be used as the initial counter in CTR:
	 * Q = V bitand (1^64 || 0^1 || 1^31 || 0^1 || 1^31)
	 */
	iv[8] &= 0x7f;
	iv[12] &= 0x7f;

	/* CTR */

	tfm2 = crypto_alloc_skcipher("ctr(aes)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm2))
		return PTR_ERR(tfm2);
	/* K2 for CTR */
	res = crypto_skcipher_setkey(tfm2, key + key_len, key_len);
	if (res) {
		crypto_free_skcipher(tfm2);
		return res;
	}

	req = skcipher_request_alloc(tfm2, GFP_KERNEL);
	if (!req) {
		crypto_free_skcipher(tfm2);
		return -ENOMEM;
	}

	sg_init_one(src, iv_crypt + AES_BLOCK_SIZE, crypt_len);
	sg_init_one(dst, out, crypt_len);
	skcipher_request_set_crypt(req, src, dst, crypt_len, iv);
	res = crypto_skcipher_decrypt(req);
	skcipher_request_free(req);
	crypto_free_skcipher(tfm2);
	if (res)
		return res;

	/* S2V */

	tfm = crypto_alloc_shash("cmac(aes)", 0, 0);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);
	/* K1 for S2V */
	res = crypto_shash_setkey(tfm, key, key_len);
	if (!res)
		res = aes_s2v(tfm, num_elem, addr, len, check);
	crypto_free_shash(tfm);
	if (res)
		return res;
	if (memcmp(check, frame_iv, AES_BLOCK_SIZE) != 0)
		return -EINVAL;
	return 0;
}