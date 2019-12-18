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
struct scatterlist {int length; scalar_t__ offset; } ;
struct decryptor_desc {int fraglen; int fragno; int /*<<< orphan*/ * frags; int /*<<< orphan*/  req; int /*<<< orphan*/  iv; } ;
struct crypto_sync_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int crypto_skcipher_decrypt (int /*<<< orphan*/ ) ; 
 int crypto_sync_skcipher_blocksize (struct crypto_sync_skcipher*) ; 
 struct crypto_sync_skcipher* crypto_sync_skcipher_reqtfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decryptor(struct scatterlist *sg, void *data)
{
	struct decryptor_desc *desc = data;
	int thislen = desc->fraglen + sg->length;
	struct crypto_sync_skcipher *tfm =
		crypto_sync_skcipher_reqtfm(desc->req);
	int fraglen, ret;

	/* Worst case is 4 fragments: head, end of page 1, start
	 * of page 2, tail.  Anything more is a bug. */
	BUG_ON(desc->fragno > 3);
	sg_set_page(&desc->frags[desc->fragno], sg_page(sg), sg->length,
		    sg->offset);
	desc->fragno++;
	desc->fraglen += sg->length;

	fraglen = thislen & (crypto_sync_skcipher_blocksize(tfm) - 1);
	thislen -= fraglen;

	if (thislen == 0)
		return 0;

	sg_mark_end(&desc->frags[desc->fragno - 1]);

	skcipher_request_set_crypt(desc->req, desc->frags, desc->frags,
				   thislen, desc->iv);

	ret = crypto_skcipher_decrypt(desc->req);
	if (ret)
		return ret;

	sg_init_table(desc->frags, 4);

	if (fraglen) {
		sg_set_page(&desc->frags[0], sg_page(sg), fraglen,
				sg->offset + sg->length - fraglen);
		desc->fragno = 1;
		desc->fraglen = fraglen;
	} else {
		desc->fragno = 0;
		desc->fraglen = 0;
	}
	return 0;
}