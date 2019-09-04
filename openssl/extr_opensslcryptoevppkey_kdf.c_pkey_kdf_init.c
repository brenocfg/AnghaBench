#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; TYPE_1__* pmeth; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_KDF_CTX_new_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_kdf_init(EVP_PKEY_CTX *ctx)
{
    EVP_KDF_CTX *kctx;

    kctx = EVP_KDF_CTX_new_id(ctx->pmeth->pkey_id);
    if (kctx == NULL)
        return 0;

    ctx->data = kctx;
    return 1;
}