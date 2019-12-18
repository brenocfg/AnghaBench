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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int HMAC_Init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_prov_digest_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ossl_prov_digest_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_digest_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hmac_init(void *vmacctx)
{
    struct hmac_data_st *macctx = vmacctx;
    const EVP_MD *digest = ossl_prov_digest_md(&macctx->digest);
    int rv = 1;

    /* HMAC_Init_ex doesn't tolerate all zero params, so we must be careful */
    if (digest != NULL)
        rv = HMAC_Init_ex(macctx->ctx, NULL, 0, digest,
                          ossl_prov_digest_engine(&macctx->digest));
    ossl_prov_digest_reset(&macctx->digest);
    return rv;
}