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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct deu_hash_t {int KIDX; int /*<<< orphan*/  KEY; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCL_SECT_END ; 
 int /*<<< orphan*/  CRTCL_SECT_START ; 
 scalar_t__ HASH_START ; 

__attribute__((used)) static int md5_hmac_setkey_hw(const u8 *key, unsigned int keylen)
{
    volatile struct deu_hash_t *hash = (struct deu_hash_t *) HASH_START;
    unsigned long flag;
    int i, j;
    u32 *in_key = (u32 *)key;        

    //printk("\nsetkey keylen: %d\n key: ", keylen);
    
    CRTCL_SECT_START;
    j = 0;
    for (i = 0; i < keylen; i+=4)
    {
         hash->KIDX = j;
         asm("sync");
         hash->KEY = *((u32 *) in_key + j); 
         asm("sync");
         j++;
    }
    CRTCL_SECT_END;

    return 0;
}