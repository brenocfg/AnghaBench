#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* ameth; } ;
struct TYPE_10__ {TYPE_1__* pmeth; TYPE_4__* pkey; } ;
struct TYPE_9__ {int (* pkey_public_check ) (TYPE_4__*) ;} ;
struct TYPE_8__ {int (* public_check ) (TYPE_4__*) ;} ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_PUBLIC_CHECK ; 
 int /*<<< orphan*/  EVP_R_NO_KEY_SET ; 
 int /*<<< orphan*/  EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*) ; 
 int stub2 (TYPE_4__*) ; 

int EVP_PKEY_public_check(EVP_PKEY_CTX *ctx)
{
    EVP_PKEY *pkey = ctx->pkey;

    if (pkey == NULL) {
        EVPerr(EVP_F_EVP_PKEY_PUBLIC_CHECK, EVP_R_NO_KEY_SET);
        return 0;
    }

    /* call customized public key check function first */
    if (ctx->pmeth->public_check != NULL)
        return ctx->pmeth->public_check(pkey);

    /* use default public key check function in ameth */
    if (pkey->ameth == NULL || pkey->ameth->pkey_public_check == NULL) {
        EVPerr(EVP_F_EVP_PKEY_PUBLIC_CHECK,
               EVP_R_OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE);
        return -2;
    }

    return pkey->ameth->pkey_public_check(pkey);
}