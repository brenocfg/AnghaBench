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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  char u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct md5_hmac_ctx {int byte_count; int* block; int dbn; char* hash; } ;
struct TYPE_2__ {int GO; int /*<<< orphan*/  DGRY; scalar_t__ BSY; } ;
struct deu_hash_t {int DBN; char MR; char D1R; char D2R; char D3R; char D4R; char D5R; TYPE_1__ controlr; } ;
typedef  int /*<<< orphan*/  MD5_HASH_WORDS ;
typedef  int /*<<< orphan*/  MD5_BLOCK_WORDS ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCL_SECT_END ; 
 int /*<<< orphan*/  CRTCL_SECT_START ; 
 scalar_t__ HASH_START ; 
 int* IFX_HASH_CON ; 
 int MD5_HMAC_DBN_TEMP_SIZE ; 
 struct md5_hmac_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int endian_swap (int) ; 
 int /*<<< orphan*/  md5_hmac_transform (struct shash_desc*,int*) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 char* temp ; 

__attribute__((used)) static int md5_hmac_final(struct shash_desc *desc, u8 *out)
{
    struct md5_hmac_ctx *mctx = crypto_shash_ctx(desc->tfm);
    const unsigned int offset = mctx->byte_count & 0x3f;
    char *p = (char *)mctx->block + offset;
    int padding = 56 - (offset + 1);
    volatile struct deu_hash_t *hashs = (struct deu_hash_t *) HASH_START;
    unsigned long flag;
    int i = 0;
    int dbn;
    u32 *in = &temp[0];


    *p++ = 0x80;
    if (padding < 0) {
        memset(p, 0x00, padding + sizeof (u64));
        md5_hmac_transform(desc, mctx->block);
        p = (char *)mctx->block;
        padding = 56;
    }

    memset(p, 0, padding);
    mctx->block[14] = endian_swap((mctx->byte_count + 64) << 3); // need to add 512 bit of the IPAD operation 
    mctx->block[15] = 0x00000000;

    md5_hmac_transform(desc, mctx->block);

    CRTCL_SECT_START;

    //printk("\ndbn = %d\n", mctx->dbn); 
    hashs->DBN = mctx->dbn;
    asm("sync");
    
    *IFX_HASH_CON = 0x0703002D; //khs, go, init, ndc, endi, kyue, hmen, md5 	

    //wait for processing
    while (hashs->controlr.BSY) {
        // this will not take long
    }

    for (dbn = 0; dbn < mctx->dbn; dbn++)
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

    /* reset the context after we finish with the hash */
    mctx->byte_count = 0;
    memset(&mctx->hash[0], 0, sizeof(MD5_HASH_WORDS));
    memset(&mctx->block[0], 0, sizeof(MD5_BLOCK_WORDS));
    memset(&temp[0], 0, MD5_HMAC_DBN_TEMP_SIZE);

    CRTCL_SECT_END;


   return 0;
}