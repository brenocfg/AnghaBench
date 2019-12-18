#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ operation; TYPE_1__* pmeth; } ;
struct TYPE_5__ {int (* keygen ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_KEYGEN ; 
 scalar_t__ EVP_PKEY_OP_KEYGEN ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVP_R_OPERATON_NOT_INITIALIZED ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

int EVP_PKEY_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY **ppkey)
{
    int ret;

    if (!ctx || !ctx->pmeth || !ctx->pmeth->keygen) {
        EVPerr(EVP_F_EVP_PKEY_KEYGEN,
               EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }
    if (ctx->operation != EVP_PKEY_OP_KEYGEN) {
        EVPerr(EVP_F_EVP_PKEY_KEYGEN, EVP_R_OPERATON_NOT_INITIALIZED);
        return -1;
    }

    if (ppkey == NULL)
        return -1;

    if (*ppkey == NULL)
        *ppkey = EVP_PKEY_new();
    if (*ppkey == NULL)
        return -1;

    ret = ctx->pmeth->keygen(ctx, *ppkey);
    if (ret <= 0) {
        EVP_PKEY_free(*ppkey);
        *ppkey = NULL;
    }
    return ret;
}