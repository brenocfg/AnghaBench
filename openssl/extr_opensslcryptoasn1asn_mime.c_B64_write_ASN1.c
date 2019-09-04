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
 int /*<<< orphan*/  ASN1_F_B64_WRITE_ASN1 ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_f_base64 () ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int i2d_ASN1_bio_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int B64_write_ASN1(BIO *out, ASN1_VALUE *val, BIO *in, int flags,
                          const ASN1_ITEM *it)
{
    BIO *b64;
    int r;
    b64 = BIO_new(BIO_f_base64());
    if (b64 == NULL) {
        ASN1err(ASN1_F_B64_WRITE_ASN1, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    /*
     * prepend the b64 BIO so all data is base64 encoded.
     */
    out = BIO_push(b64, out);
    r = i2d_ASN1_bio_stream(out, val, in, flags, it);
    (void)BIO_flush(out);
    BIO_pop(out);
    BIO_free(b64);
    return r;
}