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
struct TYPE_4__ {int /*<<< orphan*/  keymgmt; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_1__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_OP_UNDEFINED ; 
 int /*<<< orphan*/  const* evp_keymgmt_importdomparam_types (int /*<<< orphan*/ ) ; 
 scalar_t__ fromdata_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

const OSSL_PARAM *EVP_PKEY_key_fromdata_settable(EVP_PKEY_CTX *ctx)
{
    /* We call fromdata_init to get ctx->keymgmt populated */
    if (fromdata_init(ctx, EVP_PKEY_OP_UNDEFINED))
        return evp_keymgmt_importdomparam_types(ctx->keymgmt);
    return NULL;
}