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
struct TYPE_10__ {int /*<<< orphan*/  provctx; TYPE_1__* cipher; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int* data; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* ctx_set_params ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/ * prov; } ;
typedef  TYPE_2__ OSSL_PARAM ;
typedef  TYPE_3__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPH_NO_PADDING ; 
 int /*<<< orphan*/  EVP_F_EVP_CIPHER_CTX_SET_PADDING ; 
 int /*<<< orphan*/  EVP_R_CTRL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CIPHER_PARAM_PADDING ; 
 TYPE_2__ OSSL_PARAM_END ; 
 TYPE_2__ OSSL_PARAM_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

int EVP_CIPHER_CTX_set_padding(EVP_CIPHER_CTX *ctx, int pad)
{
    if (pad)
        ctx->flags &= ~EVP_CIPH_NO_PADDING;
    else
        ctx->flags |= EVP_CIPH_NO_PADDING;

    if (ctx->cipher != NULL && ctx->cipher->prov != NULL) {
        OSSL_PARAM params[] = {
            OSSL_PARAM_int(OSSL_CIPHER_PARAM_PADDING, NULL),
            OSSL_PARAM_END
        };

        params[0].data = &pad;

        if (ctx->cipher->ctx_set_params == NULL) {
            EVPerr(EVP_F_EVP_CIPHER_CTX_SET_PADDING, EVP_R_CTRL_NOT_IMPLEMENTED);
            return 0;
        }

        if (!ctx->cipher->ctx_set_params(ctx->provctx, params))
            return 0;
    }

    return 1;
}