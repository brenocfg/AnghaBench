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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct sha1_hmac_ctx {int count; int dbn; int /*<<< orphan*/ * buffer; } ;
struct TYPE_2__ {int GO; int /*<<< orphan*/  DGRY; scalar_t__ BSY; } ;
struct deu_hash_t {int DBN; int MR; int D1R; int D2R; int D3R; int D4R; int D5R; TYPE_1__ controlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCL_SECT_END ; 
 int /*<<< orphan*/  CRTCL_SECT_START ; 
 int /*<<< orphan*/  HASH_CON_VALUE ; 
 scalar_t__ HASH_START ; 
 int /*<<< orphan*/ * IFX_HASH_CON ; 
 int /*<<< orphan*/  SHA1_HMAC_BLOCK_SIZE ; 
 struct sha1_hmac_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_hmac_update (struct shash_desc*,int const*,int) ; 
 int* temp ; 

__attribute__((used)) static int sha1_hmac_final(struct shash_desc *desc, u8 *out)
{
    //struct sha1_hmac_ctx *sctx = shash_desc_ctx(desc);
    struct sha1_hmac_ctx *sctx =  crypto_shash_ctx(desc->tfm);
    u32 index, padlen;
    u64 t;
    u8 bits[8] = { 0, };
    static const u8 padding[64] = { 0x80, };
    volatile struct deu_hash_t *hashs = (struct deu_hash_t *) HASH_START;
    unsigned long flag;
    int i = 0;
    int dbn;
    u32 *in = &temp[0];
        
    t = sctx->count + 512; // need to add 512 bit of the IPAD operation
    bits[7] = 0xff & t;
    t >>= 8;
    bits[6] = 0xff & t;
    t >>= 8;
    bits[5] = 0xff & t;
    t >>= 8;
    bits[4] = 0xff & t;
    t >>= 8;
    bits[3] = 0xff & t;
    t >>= 8;
    bits[2] = 0xff & t;
    t >>= 8;
    bits[1] = 0xff & t;
    t >>= 8;
    bits[0] = 0xff & t;

    /* Pad out to 56 mod 64 */
    index = (sctx->count >> 3) & 0x3f;
    padlen = (index < 56) ? (56 - index) : ((64 + 56) - index);
    sha1_hmac_update (desc, padding, padlen);

    /* Append length */
    sha1_hmac_update (desc, bits, sizeof bits);

    CRTCL_SECT_START;
    
    hashs->DBN = sctx->dbn;
    
    //for vr9 change, ENDI = 1
    *IFX_HASH_CON = HASH_CON_VALUE; 

    //wait for processing
    while (hashs->controlr.BSY) {
        // this will not take long
    }

    for (dbn = 0; dbn < sctx->dbn; dbn++)
    {
    for (i = 0; i < 16; i++) {
        hashs->MR = in[i];
    };

    hashs->controlr.GO = 1;
    asm("sync");

    //wait for processing
    while (hashs->controlr.BSY) {
            // this will not take long
    }
    
    in += 16;
}


#if 1
    //wait for digest ready
    while (! hashs->controlr.DGRY) {
        // this will not take long
    }
#endif

    *((u32 *) out + 0) = hashs->D1R;
    *((u32 *) out + 1) = hashs->D2R;
    *((u32 *) out + 2) = hashs->D3R;
    *((u32 *) out + 3) = hashs->D4R;
    *((u32 *) out + 4) = hashs->D5R;

    memset(&sctx->buffer[0], 0, SHA1_HMAC_BLOCK_SIZE);
    sctx->count = 0; 
 
    //printk("debug ln: %d, fn: %s\n", __LINE__, __func__);
    CRTCL_SECT_END;


    return 0;

}