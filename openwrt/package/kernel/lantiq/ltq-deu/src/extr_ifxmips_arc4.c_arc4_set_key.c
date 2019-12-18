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
typedef  void* u32 ;
struct crypto_tfm {int dummy; } ;
struct arc4_t {void* K0R; void* K1R; void* K2R; void* K3R; } ;
struct TYPE_2__ {unsigned int key_length; scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ ARC4_START ; 
 int* IFX_ARC4_CON ; 
 TYPE_1__* ctx ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void**,unsigned int) ; 

__attribute__((used)) static int arc4_set_key(struct crypto_tfm *tfm, const u8 *inkey,
                       unsigned int key_len)
{
        //struct arc4_ctx *ctx = crypto_tfm_ctx(tfm);
        volatile struct arc4_t *arc4 = (struct arc4_t *) ARC4_START;
        u32 *in_key = (u32 *)inkey;
                
        // must program all bits at one go?!!!
//#if 1
        *IFX_ARC4_CON = ( (1<<31) | ((key_len - 1)<<27) | (1<<26) | (3<<16) );
        //NDC=1,ENDI=1,GO=0,KSAE=1,SM=0

        arc4->K3R = *((u32 *) in_key + 0);
        arc4->K2R = *((u32 *) in_key + 1);
        arc4->K1R = *((u32 *) in_key + 2);
        arc4->K0R = *((u32 *) in_key + 3);

#if 0 // arc4 is a ugly state machine, KSAE can only be set once per session  
        ctx->key_length = key_len;

        memcpy ((u8 *) (ctx->buf), in_key, key_len);
#endif

        return 0;
}