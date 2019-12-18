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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ MAC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int EVP_MAC_final (int /*<<< orphan*/ ,unsigned char*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MAC_size (int /*<<< orphan*/ ) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_mac_signctx(EVP_PKEY_CTX *ctx, unsigned char *sig,
                             size_t *siglen, EVP_MD_CTX *mctx)
{
    MAC_PKEY_CTX *hctx = EVP_PKEY_CTX_get_data(ctx);

    return EVP_MAC_final(hctx->ctx, sig, siglen, EVP_MAC_size(hctx->ctx));
}