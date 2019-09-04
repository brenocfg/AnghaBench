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
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_EncryptUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,unsigned char const*,size_t) ; 
 size_t INT_MAX ; 

__attribute__((used)) static int gmac_update(EVP_MAC_IMPL *gctx, const unsigned char *data,
                       size_t datalen)
{
    EVP_CIPHER_CTX *ctx = gctx->ctx;
    int outlen;

    while (datalen > INT_MAX) {
        if (!EVP_EncryptUpdate(ctx, NULL, &outlen, data, INT_MAX))
            return 0;
        data += INT_MAX;
        datalen -= INT_MAX;
    }
    return EVP_EncryptUpdate(ctx, NULL, &outlen, data, datalen);
}