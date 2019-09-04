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
struct TYPE_4__ {int /*<<< orphan*/  custom_len; int /*<<< orphan*/  custom; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void kmac_free(EVP_MAC_IMPL *kctx)
{
    if (kctx != NULL) {
        EVP_MD_CTX_free(kctx->ctx);
        OPENSSL_cleanse(kctx->key, kctx->key_len);
        OPENSSL_cleanse(kctx->custom, kctx->custom_len);
        OPENSSL_free(kctx);
    }
}