#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ param_nid; } ;
struct TYPE_11__ {int /*<<< orphan*/  dh; } ;
struct TYPE_13__ {TYPE_2__ pkey; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pkey; TYPE_1__* pmeth; TYPE_5__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY ;
typedef  TYPE_5__ DH_PKEY_CTX ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_F_PKEY_DH_KEYGEN ; 
 int /*<<< orphan*/  DH_R_NO_PARAMETERS_SET ; 
 int DH_generate_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/ * DH_new_by_nid (scalar_t__) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_copy_parameters (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_dh_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    DH_PKEY_CTX *dctx = ctx->data;
    DH *dh = NULL;

    if (ctx->pkey == NULL && dctx->param_nid == 0) {
        DHerr(DH_F_PKEY_DH_KEYGEN, DH_R_NO_PARAMETERS_SET);
        return 0;
    }
    if (dctx->param_nid != 0)
        dh = DH_new_by_nid(dctx->param_nid);
    else
        dh = DH_new();
    if (dh == NULL)
        return 0;
    EVP_PKEY_assign(pkey, ctx->pmeth->pkey_id, dh);
    /* Note: if error return, pkey is freed by parent routine */
    if (ctx->pkey != NULL && !EVP_PKEY_copy_parameters(pkey, ctx->pkey))
        return 0;
    return DH_generate_key(pkey->pkey.dh);
}