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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;

/* Variables and functions */
 scalar_t__ ASN1_BIO ; 
 int /*<<< orphan*/  ASN1_COMPARE ; 
 int /*<<< orphan*/  ASN1_DECODE ; 
 int /*<<< orphan*/  ASN1_ENCODE ; 
 int /*<<< orphan*/  ASN1_OK ; 
 int /*<<< orphan*/ * ASN1_item_d2i (int /*<<< orphan*/ *,unsigned char const**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_item_d2i_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_item_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ASN1_item_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ ERR_GET_REASON (int /*<<< orphan*/ ) ; 
 scalar_t__ ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_peek_error () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 scalar_t__ TEST_int_eq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_ge (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_ptr_null (int /*<<< orphan*/ ) ; 
 scalar_t__ expected_error ; 
 int /*<<< orphan*/  item_type ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  test_file ; 

__attribute__((used)) static int test_bad_asn1(void)
{
    BIO *bio = NULL;
    ASN1_VALUE *value = NULL;
    int ret = 0;
    unsigned char buf[2048];
    const unsigned char *buf_ptr = buf;
    unsigned char *der = NULL;
    int derlen;
    int len;

    bio = BIO_new_file(test_file, "r");
    if (!TEST_ptr(bio))
        return 0;

    if (expected_error == ASN1_BIO) {
        if (TEST_ptr_null(ASN1_item_d2i_bio(item_type, bio, NULL)))
            ret = 1;
        goto err;
    }

    /*
     * Unless we are testing it we don't use ASN1_item_d2i_bio because it
     * performs sanity checks on the input and can reject it before the
     * decoder is called.
     */
    len = BIO_read(bio, buf, sizeof(buf));
    if (!TEST_int_ge(len, 0))
        goto err;

    value = ASN1_item_d2i(NULL, &buf_ptr, len, item_type);
    if (value == NULL) {
        if (TEST_int_eq(expected_error, ASN1_DECODE))
            ret = 1;
        goto err;
    }

    derlen = ASN1_item_i2d(value, &der, item_type);

    if (der == NULL || derlen < 0) {
        if (TEST_int_eq(expected_error, ASN1_ENCODE))
            ret = 1;
        goto err;
    }

    if (derlen != len || memcmp(der, buf, derlen) != 0) {
        if (TEST_int_eq(expected_error, ASN1_COMPARE))
            ret = 1;
        goto err;
    }

    if (TEST_int_eq(expected_error, ASN1_OK))
        ret = 1;

 err:
    /* Don't indicate success for memory allocation errors */
    if (ret == 1
        && !TEST_false(ERR_GET_REASON(ERR_peek_error()) == ERR_R_MALLOC_FAILURE))
        ret = 0;
    BIO_free(bio);
    OPENSSL_free(der);
    ASN1_item_free(value, item_type);
    return ret;
}