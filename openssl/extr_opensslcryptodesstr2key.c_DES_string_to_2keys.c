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
typedef  int /*<<< orphan*/  ks ;
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  unsigned char* DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_cbc_cksum (unsigned char const*,unsigned char**,int,int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  DES_set_key_unchecked (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_set_odd_parity (unsigned char**) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char**,unsigned char**,int) ; 
 int /*<<< orphan*/  memset (unsigned char**,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

void DES_string_to_2keys(const char *str, DES_cblock *key1, DES_cblock *key2)
{
    DES_key_schedule ks;
    int i, length;

    memset(key1, 0, 8);
    memset(key2, 0, 8);
    length = strlen(str);
    for (i = 0; i < length; i++) {
        register unsigned char j = str[i];

        if ((i % 32) < 16) {
            if ((i % 16) < 8)
                (*key1)[i % 8] ^= (j << 1);
            else
                (*key2)[i % 8] ^= (j << 1);
        } else {
            j = ((j << 4) & 0xf0) | ((j >> 4) & 0x0f);
            j = ((j << 2) & 0xcc) | ((j >> 2) & 0x33);
            j = ((j << 1) & 0xaa) | ((j >> 1) & 0x55);
            if ((i % 16) < 8)
                (*key1)[7 - (i % 8)] ^= j;
            else
                (*key2)[7 - (i % 8)] ^= j;
        }
    }
    if (length <= 8)
        memcpy(key2, key1, 8);
    DES_set_odd_parity(key1);
    DES_set_odd_parity(key2);
    DES_set_key_unchecked(key1, &ks);
    DES_cbc_cksum((const unsigned char *)str, key1, length, &ks, key1);
    DES_set_key_unchecked(key2, &ks);
    DES_cbc_cksum((const unsigned char *)str, key2, length, &ks, key2);
    OPENSSL_cleanse(&ks, sizeof(ks));
    DES_set_odd_parity(key1);
    DES_set_odd_parity(key2);
}