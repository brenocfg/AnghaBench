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
struct cmac_data_st {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_CTX_get0_cipher_ctx (int /*<<< orphan*/ ) ; 
 size_t EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t cmac_size(void *vmacctx)
{
    struct cmac_data_st *macctx = vmacctx;

    return EVP_CIPHER_CTX_block_size(CMAC_CTX_get0_cipher_ctx(macctx->ctx));
}