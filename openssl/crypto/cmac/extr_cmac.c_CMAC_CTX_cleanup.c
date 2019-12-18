#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nlast_block; int /*<<< orphan*/  last_block; int /*<<< orphan*/  k2; int /*<<< orphan*/  k1; int /*<<< orphan*/  tbl; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_1__ CMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MAX_BLOCK_LENGTH ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CMAC_CTX_cleanup(CMAC_CTX *ctx)
{
    EVP_CIPHER_CTX_reset(ctx->cctx);
    OPENSSL_cleanse(ctx->tbl, EVP_MAX_BLOCK_LENGTH);
    OPENSSL_cleanse(ctx->k1, EVP_MAX_BLOCK_LENGTH);
    OPENSSL_cleanse(ctx->k2, EVP_MAX_BLOCK_LENGTH);
    OPENSSL_cleanse(ctx->last_block, EVP_MAX_BLOCK_LENGTH);
    ctx->nlast_block = -1;
}