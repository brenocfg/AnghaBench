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
typedef  int /*<<< orphan*/  X509_REQ ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_REQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_REQ_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_REQ_get0_sm2_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_REQ_set0_sm2_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_f ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int test_req_sm2_id(void)
{
    /* we only need an X509_REQ structure, no matter if it's a real SM2 cert */
    X509_REQ *x = NULL;
    BIO *bio = NULL;
    int ret = 0;
    ASN1_OCTET_STRING *v = NULL, *v2 = NULL;
    char *sm2id = "this is an ID";

    bio = BIO_new_file(req_f, "r");
    if (bio == NULL)
        goto err;

    x = PEM_read_bio_X509_REQ(bio, NULL, 0, NULL);
    if (x == NULL)
        goto err;

    v = ASN1_OCTET_STRING_new();
    if (v == NULL)
        goto err;

    if (!ASN1_OCTET_STRING_set(v, (unsigned char *)sm2id, (int)strlen(sm2id))) {
        ASN1_OCTET_STRING_free(v);
        goto err;
    }

    X509_REQ_set0_sm2_id(x, v);

    v2 = X509_REQ_get0_sm2_id(x);
    if (!TEST_ptr(v2)
            || !TEST_int_eq(ASN1_OCTET_STRING_cmp(v, v2), 0))
        goto err;

    ret = 1;
 err:
    X509_REQ_free(x);
    BIO_free(bio);
    return ret;
}