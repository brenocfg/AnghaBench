#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_6__ {int /*<<< orphan*/  senderNonce; } ;
struct TYPE_5__ {TYPE_2__* cmp_ctx; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set1_subjectName (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_ADD (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_new () ; 
 int /*<<< orphan*/ * ossl_cmp_hdr_get0_senderNonce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_HDR_get0_senderNonce_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    X509_NAME *sender = X509_NAME_new();
    ASN1_OCTET_STRING *sn;

    if (!TEST_ptr(sender))
        return 0;

    X509_NAME_ADD(sender, "CN", "A common sender name");
    if (!TEST_int_eq(OSSL_CMP_CTX_set1_subjectName(fixture->cmp_ctx, sender),
                     1))
        return 0;
    if (!TEST_int_eq(ossl_cmp_hdr_init(fixture->cmp_ctx, fixture->hdr),
                     1))
        return 0;
    sn = ossl_cmp_hdr_get0_senderNonce(fixture->hdr);
    if (!TEST_int_eq(ASN1_OCTET_STRING_cmp(fixture->cmp_ctx->senderNonce, sn),
                     0))
        return 0;
    X509_NAME_free(sender);
    return 1;
}