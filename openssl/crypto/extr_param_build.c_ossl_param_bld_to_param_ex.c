#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int curr; size_t total_blocks; size_t secure_blocks; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD_BLOCK ;
typedef  TYPE_1__ OSSL_PARAM_BLD ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 size_t ALIGN_SIZE ; 
 int /*<<< orphan*/  CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM_EX ; 
 int /*<<< orphan*/  CRYPTO_R_INSUFFICIENT_DATA_SPACE ; 
 int /*<<< orphan*/  CRYPTO_R_INSUFFICIENT_PARAM_SIZE ; 
 int /*<<< orphan*/  CRYPTO_R_INSUFFICIENT_SECURE_DATA_SPACE ; 
 int /*<<< orphan*/  CRYPTO_R_INVALID_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  param_bld_convert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

OSSL_PARAM *ossl_param_bld_to_param_ex(OSSL_PARAM_BLD *bld, OSSL_PARAM *params,
                                       size_t param_n, void *data,
                                       size_t data_n, void *secure,
                                       size_t secure_n)
{
    if (params == NULL || data == NULL) {
        CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM_EX,
                  CRYPTO_R_INVALID_NULL_ARGUMENT);
        return NULL;
    }
    if (param_n < bld->curr + 1) {
        CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM_EX,
                  CRYPTO_R_INSUFFICIENT_PARAM_SIZE);
        return NULL;
    }
    if (data_n < ALIGN_SIZE * bld->total_blocks) {
        CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM_EX,
                  CRYPTO_R_INSUFFICIENT_DATA_SPACE);
        return NULL;
    }
    if (bld->secure_blocks > 0 && secure_n < ALIGN_SIZE * bld->secure_blocks) {
        CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM_EX,
                  CRYPTO_R_INSUFFICIENT_SECURE_DATA_SPACE);
        return NULL;
    }
    param_bld_convert(bld, params, (OSSL_PARAM_BLD_BLOCK *)data,
                      (OSSL_PARAM_BLD_BLOCK *)secure);
    return params;
}