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
struct TYPE_6__ {int cofactor_mode; int /*<<< orphan*/  kdf_type; } ;
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_2__ EC_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_PKEY_EC_INIT ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_ECDH_KDF_NONE ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int pkey_ec_init(EVP_PKEY_CTX *ctx)
{
    EC_PKEY_CTX *dctx;

    if ((dctx = OPENSSL_zalloc(sizeof(*dctx))) == NULL) {
        ECerr(EC_F_PKEY_EC_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    dctx->cofactor_mode = -1;
    dctx->kdf_type = EVP_PKEY_ECDH_KDF_NONE;
    ctx->data = dctx;
    return 1;
}