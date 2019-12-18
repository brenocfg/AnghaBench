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
 int /*<<< orphan*/  ASN1_F_B64_READ_ASN1 ; 
 int /*<<< orphan*/  ASN1_R_DECODE_ERROR ; 
 int /*<<< orphan*/ * ASN1_item_d2i_bio (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_f_base64 () ; 
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 

__attribute__((used)) static ASN1_VALUE *b64_read_asn1(BIO *bio, const ASN1_ITEM *it)
{
    BIO *b64;
    ASN1_VALUE *val;

    if ((b64 = BIO_new(BIO_f_base64())) == NULL) {
        ASN1err(ASN1_F_B64_READ_ASN1, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    bio = BIO_push(b64, bio);
    val = ASN1_item_d2i_bio(it, bio, NULL);
    if (!val)
        ASN1err(ASN1_F_B64_READ_ASN1, ASN1_R_DECODE_ERROR);
    (void)BIO_flush(bio);
    BIO_pop(bio);
    BIO_free(b64);
    return val;
}