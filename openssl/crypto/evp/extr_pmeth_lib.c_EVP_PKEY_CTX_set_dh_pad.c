#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * exchprovctx; } ;
struct TYPE_9__ {TYPE_1__ kex; } ;
struct TYPE_10__ {TYPE_2__ op; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_3__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_EVP ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_DH_PAD ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_IS_DERIVE_OP (TYPE_3__*) ; 
 int EVP_PKEY_CTX_ctrl (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_CTX_set_params (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_DH ; 
 int /*<<< orphan*/  EVP_PKEY_OP_DERIVE ; 
 int /*<<< orphan*/  EVP_R_COMMAND_NOT_SUPPORTED ; 
 int /*<<< orphan*/  OSSL_EXCHANGE_PARAM_PAD ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_end () ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_uint (int /*<<< orphan*/ ,unsigned int*) ; 

int EVP_PKEY_CTX_set_dh_pad(EVP_PKEY_CTX *ctx, int pad)
{
    OSSL_PARAM dh_pad_params[2];
    unsigned int upad = pad;

    /* We use EVP_PKEY_CTX_ctrl return values */
    if (ctx == NULL || !EVP_PKEY_CTX_IS_DERIVE_OP(ctx)) {
        ERR_raise(ERR_LIB_EVP, EVP_R_COMMAND_NOT_SUPPORTED);
        return -2;
    }

    /* TODO(3.0): Remove this eventually when no more legacy */
    if (ctx->op.kex.exchprovctx == NULL)
        return EVP_PKEY_CTX_ctrl(ctx, EVP_PKEY_DH, EVP_PKEY_OP_DERIVE,
                                 EVP_PKEY_CTRL_DH_PAD, pad, NULL);

    dh_pad_params[0] = OSSL_PARAM_construct_uint(OSSL_EXCHANGE_PARAM_PAD, &upad);
    dh_pad_params[1] = OSSL_PARAM_construct_end();

    return EVP_PKEY_CTX_set_params(ctx, dh_pad_params);
}