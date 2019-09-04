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
struct TYPE_5__ {TYPE_1__* ciph; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cipher ) (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ PROV_AES_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  PROV_F_AES_CIPHER ; 
 int /*<<< orphan*/  PROV_R_CIPHER_OPERATION_FAILED ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ; 

__attribute__((used)) static int aes_cipher(void *vctx,
                      unsigned char *out, size_t *outl, size_t outsize,
                      const unsigned char *in, size_t inl)
{
    PROV_AES_KEY *ctx = (PROV_AES_KEY *)vctx;

    if (outsize < inl) {
        PROVerr(PROV_F_AES_CIPHER, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
        return 0;
    }

    if (!ctx->ciph->cipher(ctx, out, in, inl)) {
        PROVerr(PROV_F_AES_CIPHER, PROV_R_CIPHER_OPERATION_FAILED);
        return 0;
    }

    *outl = inl;
    return 1;
}