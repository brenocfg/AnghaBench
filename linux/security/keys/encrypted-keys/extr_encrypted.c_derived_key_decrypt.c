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
struct encrypted_key_payload {int decrypted_datalen; int /*<<< orphan*/  iv; int /*<<< orphan*/ * decrypted_data; int /*<<< orphan*/ * encrypted_data; } ;
struct crypto_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct skcipher_request*) ; 
 int PTR_ERR (struct skcipher_request*) ; 
 int /*<<< orphan*/  blksize ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  dump_decrypted_data (struct encrypted_key_payload*) ; 
 int /*<<< orphan*/  dump_encrypted_data (struct encrypted_key_payload*,unsigned int) ; 
 struct skcipher_request* init_skcipher_req (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int roundup (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int derived_key_decrypt(struct encrypted_key_payload *epayload,
			       const u8 *derived_key,
			       unsigned int derived_keylen)
{
	struct scatterlist sg_in[1];
	struct scatterlist sg_out[2];
	struct crypto_skcipher *tfm;
	struct skcipher_request *req;
	unsigned int encrypted_datalen;
	u8 iv[AES_BLOCK_SIZE];
	u8 *pad;
	int ret;

	/* Throwaway buffer to hold the unused zero padding at the end */
	pad = kmalloc(AES_BLOCK_SIZE, GFP_KERNEL);
	if (!pad)
		return -ENOMEM;

	encrypted_datalen = roundup(epayload->decrypted_datalen, blksize);
	req = init_skcipher_req(derived_key, derived_keylen);
	ret = PTR_ERR(req);
	if (IS_ERR(req))
		goto out;
	dump_encrypted_data(epayload, encrypted_datalen);

	sg_init_table(sg_in, 1);
	sg_init_table(sg_out, 2);
	sg_set_buf(sg_in, epayload->encrypted_data, encrypted_datalen);
	sg_set_buf(&sg_out[0], epayload->decrypted_data,
		   epayload->decrypted_datalen);
	sg_set_buf(&sg_out[1], pad, AES_BLOCK_SIZE);

	memcpy(iv, epayload->iv, sizeof(iv));
	skcipher_request_set_crypt(req, sg_in, sg_out, encrypted_datalen, iv);
	ret = crypto_skcipher_decrypt(req);
	tfm = crypto_skcipher_reqtfm(req);
	skcipher_request_free(req);
	crypto_free_skcipher(tfm);
	if (ret < 0)
		goto out;
	dump_decrypted_data(epayload);
out:
	kfree(pad);
	return ret;
}