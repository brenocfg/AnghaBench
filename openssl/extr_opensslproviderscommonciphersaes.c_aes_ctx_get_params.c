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
struct TYPE_2__ {int /*<<< orphan*/  pad; } ;
typedef  TYPE_1__ PROV_AES_KEY ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_PADDING ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_int (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_F_AES_CTX_GET_PARAMS ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_SET_PARAMETER ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aes_ctx_get_params(void *vctx, const OSSL_PARAM params[])
{
    PROV_AES_KEY *ctx = (PROV_AES_KEY *)vctx;
    const OSSL_PARAM *p;

    p = OSSL_PARAM_locate(params, OSSL_CIPHER_PARAM_PADDING);
    if (p != NULL && !OSSL_PARAM_set_int(p, ctx->pad)) {
        PROVerr(PROV_F_AES_CTX_GET_PARAMS, PROV_R_FAILED_TO_SET_PARAMETER);
        return 0;
    }

    return 1;
}