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

__attribute__((used)) static int sha1_hmac_setkey_hw(const u8 *key, unsigned int keylen)
{
    volatile struct deu_hash_t *hash = (struct deu_hash_t *) HASH_START;
    int i, j;
    unsigned long flag;
    u32 *in_key = (u32 *)key;        

    j = 0;

    CRTCL_SECT_START;
    for (i = 0; i < keylen; i+=4)
    {
         hash->KIDX = j;
         asm("sync");
         hash->KEY = *((u32 *) in_key + j); 
         j++;
    }

    CRTCL_SECT_END;
    return 0;
}