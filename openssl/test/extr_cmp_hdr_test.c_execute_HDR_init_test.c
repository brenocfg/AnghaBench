#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * recipNonce; int /*<<< orphan*/ * transactionID; int /*<<< orphan*/ * senderNonce; } ;
struct TYPE_4__ {scalar_t__ expected; TYPE_2__* cmp_ctx; int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ CMP_HDR_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_CMP_HDR_get0_recipNonce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OSSL_CMP_HDR_get0_transactionID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CMP_PVNO ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/ * ossl_cmp_hdr_get0_senderNonce (int /*<<< orphan*/ ) ; 
 scalar_t__ ossl_cmp_hdr_get_pvno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_HDR_init_test(CMP_HDR_TEST_FIXTURE *fixture)
{
    ASN1_OCTET_STRING *header_nonce = NULL;
    ASN1_OCTET_STRING *ctx_nonce = NULL;
    int res = 0;

    if (!TEST_int_eq(fixture->expected,
                     ossl_cmp_hdr_init(fixture->cmp_ctx, fixture->hdr)))
        goto err;
    if (fixture->expected != 0) {
        if (!TEST_int_eq(ossl_cmp_hdr_get_pvno(fixture->hdr), OSSL_CMP_PVNO)
                || !TEST_true(0 == ASN1_OCTET_STRING_cmp(
                        ossl_cmp_hdr_get0_senderNonce(fixture->hdr),
                        fixture->cmp_ctx->senderNonce))
                || !TEST_true(0 ==  ASN1_OCTET_STRING_cmp(
                            OSSL_CMP_HDR_get0_transactionID(fixture->hdr),
                            fixture->cmp_ctx->transactionID)))
            goto err;
        header_nonce = OSSL_CMP_HDR_get0_recipNonce(fixture->hdr);
        ctx_nonce = fixture->cmp_ctx->recipNonce;
        if (ctx_nonce != NULL
                && (!TEST_ptr(header_nonce)
                || !TEST_int_eq(0, ASN1_OCTET_STRING_cmp(header_nonce,
                                                         ctx_nonce))))
            goto err;
    }

    res = 1;

 err:
    return res;
}