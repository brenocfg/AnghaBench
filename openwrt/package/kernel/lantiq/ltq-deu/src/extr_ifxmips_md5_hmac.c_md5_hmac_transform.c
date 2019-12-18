#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct md5_hmac_ctx {int dbn; } ;

/* Variables and functions */
 int MD5_HMAC_DBN_TEMP_SIZE ; 
 struct md5_hmac_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/ * temp ; 

__attribute__((used)) static void md5_hmac_transform(struct shash_desc *desc, u32 const *in)
{
    struct md5_hmac_ctx *mctx = crypto_shash_ctx(desc->tfm);

    memcpy(&temp[mctx->dbn<<4], in, 64); //dbn workaround
    mctx->dbn += 1;
    
    if ( (mctx->dbn<<4) > MD5_HMAC_DBN_TEMP_SIZE )
    {
        printk("MD5_HMAC_DBN_TEMP_SIZE exceeded\n");
    }

}