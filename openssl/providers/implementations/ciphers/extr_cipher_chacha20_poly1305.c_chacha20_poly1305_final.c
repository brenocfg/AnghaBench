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
struct TYPE_5__ {scalar_t__ hw; } ;
struct TYPE_4__ {scalar_t__ (* aead_cipher ) (TYPE_2__*,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ PROV_CIPHER_HW_CHACHA20_POLY1305 ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__*,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chacha20_poly1305_final(void *vctx, unsigned char *out, size_t *outl,
                                   size_t outsize)
{
    PROV_CIPHER_CTX *ctx = (PROV_CIPHER_CTX *)vctx;
    PROV_CIPHER_HW_CHACHA20_POLY1305 *hw =
        (PROV_CIPHER_HW_CHACHA20_POLY1305 *)ctx->hw;

    if (hw->aead_cipher(ctx, out, outl, NULL, 0) <= 0)
        return 0;

    *outl = 0;
    return 1;
}