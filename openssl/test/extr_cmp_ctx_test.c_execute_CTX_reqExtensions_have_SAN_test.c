#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSIONS ;
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ OSSL_CMP_CTX_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  OSSL_CMP_CTX ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_OCTET_STRING_new () ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char*,int const) ; 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int OSSL_CMP_CTX_reqExtensions_have_SAN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set0_reqExtensions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RAND_bytes (unsigned char*,int const) ; 
 int TEST_false (int) ; 
 scalar_t__ TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_EXTENSION_create_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_EXTENSION_new_null () ; 
 int /*<<< orphan*/ * sk_X509_EXTENSION_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int execute_CTX_reqExtensions_have_SAN_test(
                                             OSSL_CMP_CTX_TEST_FIXTURE *fixture)
{
    OSSL_CMP_CTX *ctx = fixture->ctx;
    const int len = 16;
    unsigned char str[16 /* = len */ ];
    ASN1_OCTET_STRING *data = NULL;
    X509_EXTENSION *ext = NULL;
    X509_EXTENSIONS *exts = NULL;
    int res = 0;

    if (!TEST_false(OSSL_CMP_CTX_reqExtensions_have_SAN(ctx)))
        return 0;

    if (!TEST_int_eq(1, RAND_bytes(str, len))
            || !TEST_ptr(data = ASN1_OCTET_STRING_new())
            || !TEST_true(ASN1_OCTET_STRING_set(data, str, len)))
        goto err;
    ext = X509_EXTENSION_create_by_NID(NULL, NID_subject_alt_name, 0, data);
    if (!TEST_ptr(ext)
            || !TEST_ptr(exts = sk_X509_EXTENSION_new_null())
            || !TEST_true(sk_X509_EXTENSION_push(exts, ext))
            || !TEST_true(OSSL_CMP_CTX_set0_reqExtensions(ctx, exts))) {
        X509_EXTENSION_free(ext);
        sk_X509_EXTENSION_free(exts);
        goto err;
    }
    if (TEST_int_eq(OSSL_CMP_CTX_reqExtensions_have_SAN(ctx), 1)) {
        ext = sk_X509_EXTENSION_pop(exts);
        res = TEST_false(OSSL_CMP_CTX_reqExtensions_have_SAN(ctx));
        X509_EXTENSION_free(ext);
    }
 err:
    ASN1_OCTET_STRING_free(data);
    return res;
}