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
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_GET_TAG ; 
 int /*<<< orphan*/  EVP_EncryptFinal_ex (int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int /*<<< orphan*/  gmac_size (TYPE_1__*) ; 

__attribute__((used)) static int gmac_final(EVP_MAC_IMPL *gctx, unsigned char *out)
{
    int hlen;

    if (!EVP_EncryptFinal_ex(gctx->ctx, out, &hlen)
        || !EVP_CIPHER_CTX_ctrl(gctx->ctx, EVP_CTRL_AEAD_GET_TAG,
                                gmac_size(gctx), out))
        return 0;
    return 1;
}