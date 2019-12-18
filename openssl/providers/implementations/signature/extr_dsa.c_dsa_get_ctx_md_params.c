#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mdctx; } ;
typedef  TYPE_1__ PROV_DSA_CTX ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int EVP_MD_CTX_get_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsa_get_ctx_md_params(void *vpdsactx, OSSL_PARAM *params)
{
    PROV_DSA_CTX *pdsactx = (PROV_DSA_CTX *)vpdsactx;

    if (pdsactx->mdctx == NULL)
        return 0;

    return EVP_MD_CTX_get_params(pdsactx->mdctx, params);
}