#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t data_size; int /*<<< orphan*/  data_type; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int curr; size_t const total_blocks; size_t const secure_blocks; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD_BLOCK ;
typedef  TYPE_1__ OSSL_PARAM_BLD ;
typedef  TYPE_2__ OSSL_PARAM ;

/* Variables and functions */
 size_t const ALIGN_SIZE ; 
 int /*<<< orphan*/  CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM ; 
 int /*<<< orphan*/  CRYPTO_R_SECURE_MALLOC_FAILURE ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_2__* OPENSSL_malloc (size_t const) ; 
 int /*<<< orphan*/  OPENSSL_secure_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_secure_malloc (size_t const) ; 
 int /*<<< orphan*/  OSSL_PARAM_ALLOCATED_END ; 
 size_t bytes_to_blocks (int) ; 
 TYPE_2__* param_bld_convert (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

OSSL_PARAM *ossl_param_bld_to_param(OSSL_PARAM_BLD *bld)
{
    OSSL_PARAM_BLD_BLOCK *blk, *s = NULL;
    OSSL_PARAM *params, *last;
    const size_t p_blks = bytes_to_blocks((1 + bld->curr) * sizeof(*params));
    const size_t total = ALIGN_SIZE * (p_blks + bld->total_blocks);
    const size_t ss = ALIGN_SIZE * bld->secure_blocks;

    if (ss > 0) {
        s = OPENSSL_secure_malloc(ss);
        if (s == NULL) {
            CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM,
                      CRYPTO_R_SECURE_MALLOC_FAILURE);
            return NULL;
        }
    }
    params = OPENSSL_malloc(total);
    if (params == NULL) {
        CRYPTOerr(CRYPTO_F_OSSL_PARAM_BLD_TO_PARAM, ERR_R_MALLOC_FAILURE);
        OPENSSL_secure_free(s);
        return NULL;
    }
    blk = p_blks + (OSSL_PARAM_BLD_BLOCK *)(params);
    last = param_bld_convert(bld, params, blk, s);
    last->data_size = ss;
    last->data = s;
    last->data_type = OSSL_PARAM_ALLOCATED_END;
    return params;
}