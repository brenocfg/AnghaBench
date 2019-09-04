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
struct TYPE_5__ {int /*<<< orphan*/ * prov; } ;
struct TYPE_4__ {int key_len; TYPE_2__* cipher; } ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_key_length (TYPE_2__*) ; 

int EVP_CIPHER_CTX_key_length(const EVP_CIPHER_CTX *ctx)
{
    /*
     * TODO(3.0): This may need to change if/when we introduce variable length
     * key ciphers into the providers.
     */
    if (ctx->cipher != NULL && ctx->cipher->prov != NULL)
        return EVP_CIPHER_key_length(ctx->cipher);
    return ctx->key_len;
}