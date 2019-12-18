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
struct TYPE_8__ {int /*<<< orphan*/  dsa; } ;
struct TYPE_10__ {TYPE_1__ pkey; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pkey; } ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_F_PKEY_DSA_KEYGEN ; 
 int /*<<< orphan*/  DSA_R_NO_PARAMETERS_SET ; 
 int DSA_generate_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DSA_new () ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_DSA (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_copy_parameters (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_dsa_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    DSA *dsa = NULL;

    if (ctx->pkey == NULL) {
        DSAerr(DSA_F_PKEY_DSA_KEYGEN, DSA_R_NO_PARAMETERS_SET);
        return 0;
    }
    dsa = DSA_new();
    if (dsa == NULL)
        return 0;
    EVP_PKEY_assign_DSA(pkey, dsa);
    /* Note: if error return, pkey is freed by parent routine */
    if (!EVP_PKEY_copy_parameters(pkey, ctx->pkey))
        return 0;
    return DSA_generate_key(pkey->pkey.dsa);
}