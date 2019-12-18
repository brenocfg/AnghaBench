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

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DEShash (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPT_LMhash_Magic ; 

__attribute__((used)) static void CRYPT_LMhash( unsigned char *dst, const unsigned char *pwd, const int len )
{
    int i, max = 14;
    unsigned char tmp_pwd[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

    max = len > max ? max : len;

    for (i = 0; i < max; i++)
        tmp_pwd[i] = pwd[i];

    CRYPT_DEShash( dst, tmp_pwd, CRYPT_LMhash_Magic );
    CRYPT_DEShash( &dst[8], &tmp_pwd[7], CRYPT_LMhash_Magic );
}