#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int pad; size_t keylen; size_t ivlen; unsigned int mode; size_t blocksize; int /*<<< orphan*/  libctx; int /*<<< orphan*/  const* hw; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  PROV_CIPHER_HW ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  PROV_LIBRARY_CONTEXT_OF (void*) ; 

void cipher_generic_initkey(void *vctx, size_t kbits, size_t blkbits,
                            size_t ivbits, unsigned int mode, uint64_t flags,
                            const PROV_CIPHER_HW *hw, void *provctx)
{
    PROV_CIPHER_CTX *ctx = (PROV_CIPHER_CTX *)vctx;

    ctx->flags = flags;
    ctx->pad = 1;
    ctx->keylen = ((kbits) / 8);
    ctx->ivlen = ((ivbits) / 8);
    ctx->hw = hw;
    ctx->mode = mode;
    ctx->blocksize = blkbits / 8;
    if (provctx != NULL)
        ctx->libctx = PROV_LIBRARY_CONTEXT_OF(provctx); /* used for rand */
}