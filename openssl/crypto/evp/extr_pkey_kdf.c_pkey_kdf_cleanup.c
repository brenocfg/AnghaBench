#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  kctx; } ;
typedef  TYPE_1__ EVP_PKEY_KDF_CTX ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  pkey_kdf_free_collected (TYPE_1__*) ; 

__attribute__((used)) static void pkey_kdf_cleanup(EVP_PKEY_CTX *ctx)
{
    EVP_PKEY_KDF_CTX *pkctx = ctx->data;

    EVP_KDF_CTX_free(pkctx->kctx);
    pkey_kdf_free_collected(pkctx);
    OPENSSL_free(pkctx);
}