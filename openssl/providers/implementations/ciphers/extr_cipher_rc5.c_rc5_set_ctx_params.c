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
struct TYPE_2__ {unsigned int rounds; } ;
typedef  TYPE_1__ PROV_RC5_CTX ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_ROUNDS ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint (int /*<<< orphan*/  const*,unsigned int*) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate_const (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_GET_PARAMETER ; 
 int /*<<< orphan*/  PROV_R_UNSUPPORTED_NUMBER_OF_ROUNDS ; 
 unsigned int RC5_12_ROUNDS ; 
 unsigned int RC5_16_ROUNDS ; 
 unsigned int RC5_8_ROUNDS ; 
 int /*<<< orphan*/  cipher_generic_set_ctx_params (void*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int rc5_set_ctx_params(void *vctx, const OSSL_PARAM params[])
{
    PROV_RC5_CTX *ctx = (PROV_RC5_CTX *)vctx;
    const OSSL_PARAM *p;

    if (!cipher_generic_set_ctx_params(vctx, params))
        return 0;

    p = OSSL_PARAM_locate_const(params, OSSL_CIPHER_PARAM_ROUNDS);
    if (p != NULL) {
        unsigned int rounds;

        if (!OSSL_PARAM_get_uint(p, &rounds)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GET_PARAMETER);
            return 0;
        }
        if (rounds != RC5_8_ROUNDS
            && rounds != RC5_12_ROUNDS
            && rounds != RC5_16_ROUNDS) {
            ERR_raise(ERR_LIB_PROV, PROV_R_UNSUPPORTED_NUMBER_OF_ROUNDS);
            return 0;
        }
        ctx->rounds = rounds;
    }
    return 1;
}