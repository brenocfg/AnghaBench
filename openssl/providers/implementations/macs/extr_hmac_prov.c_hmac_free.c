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
struct hmac_data_st {int /*<<< orphan*/  digest; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (struct hmac_data_st*) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hmac_free(void *vmacctx)
{
    struct hmac_data_st *macctx = vmacctx;

    if (macctx != NULL) {
        HMAC_CTX_free(macctx->ctx);
        ossl_prov_digest_reset(&macctx->digest);
        OPENSSL_free(macctx);
    }
}