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
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_I2D_ASN1_BIO_STREAM ; 
 int /*<<< orphan*/  ASN1_item_i2d_bio (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_NDEF (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int SMIME_STREAM ; 
 int /*<<< orphan*/  SMIME_crlf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int i2d_ASN1_bio_stream(BIO *out, ASN1_VALUE *val, BIO *in, int flags,
                        const ASN1_ITEM *it)
{
    /* If streaming create stream BIO and copy all content through it */
    if (flags & SMIME_STREAM) {
        BIO *bio, *tbio;
        bio = BIO_new_NDEF(out, val, it);
        if (!bio) {
            ASN1err(ASN1_F_I2D_ASN1_BIO_STREAM, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        SMIME_crlf_copy(in, bio, flags);
        (void)BIO_flush(bio);
        /* Free up successive BIOs until we hit the old output BIO */
        do {
            tbio = BIO_pop(bio);
            BIO_free(bio);
            bio = tbio;
        } while (bio != out);
    }
    /*
     * else just write out ASN1 structure which will have all content stored
     * internally
     */
    else
        ASN1_item_i2d_bio(it, out, val);
    return 1;
}