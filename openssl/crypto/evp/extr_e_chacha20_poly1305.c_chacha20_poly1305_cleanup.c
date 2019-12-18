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
struct TYPE_4__ {int /*<<< orphan*/  cipher_data; } ;
typedef  TYPE_1__ EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CHACHA_AEAD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ Poly1305_ctx_size () ; 
 int /*<<< orphan*/ * aead_data (TYPE_1__*) ; 

__attribute__((used)) static int chacha20_poly1305_cleanup(EVP_CIPHER_CTX *ctx)
{
    EVP_CHACHA_AEAD_CTX *actx = aead_data(ctx);
    if (actx)
        OPENSSL_cleanse(ctx->cipher_data, sizeof(*actx) + Poly1305_ctx_size());
    return 1;
}