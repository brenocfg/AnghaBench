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
struct TYPE_4__ {int /*<<< orphan*/ * mac_ctx_init; int /*<<< orphan*/  cipher_ctx; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ SIV128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int CRYPTO_siv128_copy_ctx(SIV128_CONTEXT *dest, SIV128_CONTEXT *src)
{
    memcpy(&dest->d, &src->d, sizeof(src->d));
    if (!EVP_CIPHER_CTX_copy(dest->cipher_ctx, src->cipher_ctx))
        return 0;
    EVP_MAC_CTX_free(dest->mac_ctx_init);
    dest->mac_ctx_init = EVP_MAC_CTX_dup(src->mac_ctx_init);
    if (dest->mac_ctx_init == NULL)
        return 0;
    return 1;
}