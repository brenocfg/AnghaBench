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
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  DES_set_odd_parity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int fixup_des3_key(unsigned char *key)
{
    unsigned char *cblock;
    int i, j;

    for (i = 2; i >= 0; i--) {
        cblock = &key[i * 8];
        memmove(cblock, &key[i * 7], 7);
        cblock[7] = 0;
        for (j = 0; j < 7; j++)
            cblock[7] |= (cblock[j] & 1) << (j + 1);
        DES_set_odd_parity((DES_cblock *)cblock);
    }

    /* fail if keys are such that triple des degrades to single des */
    if (CRYPTO_memcmp(&key[0], &key[8], 8) == 0 ||
        CRYPTO_memcmp(&key[8], &key[16], 8) == 0) {
        return 0;
    }

    return 1;
}