#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* data; TYPE_1__* pmeth; } ;
struct TYPE_8__ {int /*<<< orphan*/ * kctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY_KDF_CTX ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 
 char* OBJ_nid2sn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static int pkey_kdf_init(EVP_PKEY_CTX *ctx)
{
    EVP_PKEY_KDF_CTX *pkctx;
    EVP_KDF_CTX *kctx;
    const char *kdf_name = OBJ_nid2sn(ctx->pmeth->pkey_id);
    EVP_KDF *kdf;

    pkctx = OPENSSL_zalloc(sizeof(*pkctx));
    if (pkctx == NULL)
        return 0;

    kdf = EVP_KDF_fetch(NULL, kdf_name, NULL);
    kctx = EVP_KDF_CTX_new(kdf);
    EVP_KDF_free(kdf);
    if (kctx == NULL) {
        OPENSSL_free(pkctx);
        return 0;
    }

    pkctx->kctx = kctx;
    ctx->data = pkctx;
    return 1;
}