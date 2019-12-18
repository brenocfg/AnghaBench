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
struct xdr_buf {int len; } ;
struct decryptor_desc {int /*<<< orphan*/  frags; scalar_t__ fraglen; scalar_t__ fragno; int /*<<< orphan*/  req; int /*<<< orphan*/  iv; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int crypto_sync_skcipher_blocksize (struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  decryptor ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,struct crypto_sync_skcipher*) ; 
 int /*<<< orphan*/  skcipher_request_zero (int /*<<< orphan*/ ) ; 
 int xdr_process_buf (struct xdr_buf*,int,int,int /*<<< orphan*/ ,struct decryptor_desc*) ; 

int
gss_decrypt_xdr_buf(struct crypto_sync_skcipher *tfm, struct xdr_buf *buf,
		    int offset)
{
	int ret;
	struct decryptor_desc desc;
	SYNC_SKCIPHER_REQUEST_ON_STACK(req, tfm);

	/* XXXJBF: */
	BUG_ON((buf->len - offset) % crypto_sync_skcipher_blocksize(tfm) != 0);

	skcipher_request_set_sync_tfm(req, tfm);
	skcipher_request_set_callback(req, 0, NULL, NULL);

	memset(desc.iv, 0, sizeof(desc.iv));
	desc.req = req;
	desc.fragno = 0;
	desc.fraglen = 0;

	sg_init_table(desc.frags, 4);

	ret = xdr_process_buf(buf, offset, buf->len - offset, decryptor, &desc);
	skcipher_request_zero(req);
	return ret;
}