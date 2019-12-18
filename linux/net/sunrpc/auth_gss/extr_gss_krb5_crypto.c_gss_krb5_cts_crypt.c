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
typedef  int u32 ;
struct xdr_buf {int len; struct page** pages; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int GSS_KRB5_MAX_BLOCKSIZE ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int read_bytes_from_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int write_bytes_to_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32
gss_krb5_cts_crypt(struct crypto_sync_skcipher *cipher, struct xdr_buf *buf,
		   u32 offset, u8 *iv, struct page **pages, int encrypt)
{
	u32 ret;
	struct scatterlist sg[1];
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, cipher);
	u8 *data;
	struct page **save_pages;
	u32 len = buf->len - offset;

	if (len > GSS_KRB5_MAX_BLOCKSIZE * 2) {
		WARN_ON(0);
		return -ENOMEM;
	}
	data = kmalloc(GSS_KRB5_MAX_BLOCKSIZE * 2, GFP_NOFS);
	if (!data)
		return -ENOMEM;

	/*
	 * For encryption, we want to read from the cleartext
	 * page cache pages, and write the encrypted data to
	 * the supplied xdr_buf pages.
	 */
	save_pages = buf->pages;
	if (encrypt)
		buf->pages = pages;

	ret = read_bytes_from_xdr_buf(buf, offset, data, len);
	buf->pages = save_pages;
	if (ret)
		goto out;

	sg_init_one(sg, data, len);

	skcipher_request_set_sync_tfm(req, cipher);
	skcipher_request_set_callback(req, 0, NULL, NULL);
	skcipher_request_set_crypt(req, sg, sg, len, iv);

	if (encrypt)
		ret = crypto_skcipher_encrypt(req);
	else
		ret = crypto_skcipher_decrypt(req);

	skcipher_request_zero(req);

	if (ret)
		goto out;

	ret = write_bytes_to_xdr_buf(buf, offset, data, len);

out:
	kfree(data);
	return ret;
}