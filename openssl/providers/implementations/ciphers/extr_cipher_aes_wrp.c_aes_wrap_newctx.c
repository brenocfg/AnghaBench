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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int pad; scalar_t__ ivlen; } ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;
typedef  void PROV_AES_WRAP_CTX ;

/* Variables and functions */
 scalar_t__ AES_WRAP_PAD_IVLEN ; 
 void* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  cipher_generic_initkey (TYPE_1__*,size_t,size_t,size_t,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *aes_wrap_newctx(size_t kbits, size_t blkbits,
                             size_t ivbits, unsigned int mode, uint64_t flags)
{
    PROV_AES_WRAP_CTX *wctx = OPENSSL_zalloc(sizeof(*wctx));
    PROV_CIPHER_CTX *ctx = (PROV_CIPHER_CTX *)wctx;

    if (ctx != NULL) {
        cipher_generic_initkey(ctx, kbits, blkbits, ivbits, mode, flags,
                               NULL, NULL);
        ctx->pad = (ctx->ivlen == AES_WRAP_PAD_IVLEN);
    }
    return wctx;
}