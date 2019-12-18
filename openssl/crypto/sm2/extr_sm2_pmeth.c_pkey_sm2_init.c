#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  SM2_PKEY_CTX ;
typedef  TYPE_1__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SM2_F_PKEY_SM2_INIT ; 
 int /*<<< orphan*/  SM2err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_sm2_init(EVP_PKEY_CTX *ctx)
{
    SM2_PKEY_CTX *smctx;

    if ((smctx = OPENSSL_zalloc(sizeof(*smctx))) == NULL) {
        SM2err(SM2_F_PKEY_SM2_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    ctx->data = smctx;
    return 1;
}