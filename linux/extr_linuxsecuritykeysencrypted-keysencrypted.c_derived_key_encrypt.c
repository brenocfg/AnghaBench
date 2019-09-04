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
struct skcipher_request {int dummy; } ;
struct scatterlist {int dummy; } ;
struct encrypted_key_payload {unsigned int decrypted_datalen; int /*<<< orphan*/  iv; int /*<<< orphan*/  encrypted_data; int /*<<< orphan*/  decrypted_data; } ;
struct crypto_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 scalar_t__ IS_ERR (struct skcipher_request*) ; 
 int PTR_ERR (struct skcipher_request*) ; 
 int /*<<< orphan*/  ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blksize ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  dump_decrypted_data (struct encrypted_key_payload*) ; 
 int /*<<< orphan*/  dump_encrypted_data (struct encrypted_key_payload*,unsigned int) ; 
 struct skcipher_request* init_skcipher_req (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 unsigned int roundup (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int derived_key_encrypt(struct encrypted_key_payload *epayload,
			       const u8 *derived_key,
			       unsigned int derived_keylen)
{
	struct scatterlist sg_in[2];
	struct scatterlist sg_out[1];
	struct crypto_skcipher *tfm;
	struct skcipher_request *req;
	unsigned int encrypted_datalen;
	u8 iv[AES_BLOCK_SIZE];
	int ret;

	encrypted_datalen = roundup(epayload->decrypted_datalen, blksize);

	req = init_skcipher_req(derived_key, derived_keylen);
	ret = PTR_ERR(req);
	if (IS_ERR(req))
		goto out;
	dump_decrypted_data(epayload);

	sg_init_table(sg_in, 2);
	sg_set_buf(&sg_in[0], epayload->decrypted_data,
		   epayload->decrypted_datalen);
	sg_set_page(&sg_in[1], ZERO_PAGE(0), AES_BLOCK_SIZE, 0);

	sg_init_table(sg_out, 1);
	sg_set_buf(sg_out, epayload->encrypted_data, encrypted_datalen);

	memcpy(iv, epayload->iv, sizeof(iv));
	skcipher_request_set_crypt(req, sg_in, sg_out, encrypted_datalen, iv);
	ret = crypto_skcipher_encrypt(req);
	tfm = crypto_skcipher_reqtfm(req);
	skcipher_request_free(req);
	crypto_free_skcipher(tfm);
	if (ret < 0)
		pr_err("encrypted_key: failed to encrypt (%d)\n", ret);
	else
		dump_encrypted_data(epayload, encrypted_datalen);
out:
	return ret;
}