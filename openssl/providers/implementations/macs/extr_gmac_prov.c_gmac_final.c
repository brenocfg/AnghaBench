#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gmac_data_st {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_GET_TAG ; 
 int /*<<< orphan*/  EVP_EncryptFinal_ex (int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int gmac_size () ; 

__attribute__((used)) static int gmac_final(void *vmacctx, unsigned char *out, size_t *outl,
                      size_t outsize)
{
    struct gmac_data_st *macctx = vmacctx;
    int hlen = 0;

    if (!EVP_EncryptFinal_ex(macctx->ctx, out, &hlen))
        return 0;

    /* TODO(3.0) Use params */
    hlen = gmac_size();
    if (!EVP_CIPHER_CTX_ctrl(macctx->ctx, EVP_CTRL_AEAD_GET_TAG,
                             hlen, out))
        return 0;

    *outl = hlen;
    return 1;
}