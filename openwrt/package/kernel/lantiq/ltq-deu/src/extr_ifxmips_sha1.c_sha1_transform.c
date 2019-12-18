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
typedef  void* u32 ;
struct sha1_ctx {int started; scalar_t__ hash; } ;
struct TYPE_2__ {scalar_t__ BSY; } ;
struct deu_hash_t {void* MR; void* D5R; void* D4R; void* D3R; void* D2R; void* D1R; TYPE_1__ controlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCL_SECT_END ; 
 int /*<<< orphan*/  CRTCL_SECT_START ; 
 scalar_t__ HASH_START ; 

__attribute__((used)) static void sha1_transform (struct sha1_ctx *sctx, u32 *state, const u32 *in)
{
    int i = 0;
    volatile struct deu_hash_t *hashs = (struct deu_hash_t *) HASH_START;
    unsigned long flag;

    CRTCL_SECT_START;

    /* For context switching purposes, the previous hash output
     * is loaded back into the output register 
    */
    if (sctx->started) {
        hashs->D1R = *((u32 *) sctx->hash + 0);
        hashs->D2R = *((u32 *) sctx->hash + 1);
        hashs->D3R = *((u32 *) sctx->hash + 2);
        hashs->D4R = *((u32 *) sctx->hash + 3);
        hashs->D5R = *((u32 *) sctx->hash + 4);
    }

    for (i = 0; i < 16; i++) {
        hashs->MR = in[i];
    };

    //wait for processing
    while (hashs->controlr.BSY) {
        // this will not take long
    }
   
    /* For context switching purposes, the output is saved into a 
     * context struct which can be used later on 
    */
    *((u32 *) sctx->hash + 0) = hashs->D1R;
    *((u32 *) sctx->hash + 1) = hashs->D2R;
    *((u32 *) sctx->hash + 2) = hashs->D3R;
    *((u32 *) sctx->hash + 3) = hashs->D4R;
    *((u32 *) sctx->hash + 4) = hashs->D5R;

    sctx->started = 1;

    CRTCL_SECT_END;
}