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
typedef  int /*<<< orphan*/  RC2_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  RC2_DECRYPT ; 
 int /*<<< orphan*/  RC2_ENCRYPT ; 
 int /*<<< orphan*/  RC2_ecb_encrypt (unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RC2_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned char** RC2cipher ; 
 int /*<<< orphan*/ ** RC2key ; 
 unsigned char** RC2plain ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 

__attribute__((used)) static int test_rc2(const int n)
{
    int testresult = 1;
    RC2_KEY key;
    unsigned char buf[8], buf2[8];

    RC2_set_key(&key, 16, &(RC2key[n][0]), 0 /* or 1024 */ );

    RC2_ecb_encrypt(&RC2plain[n][0], buf, &key, RC2_ENCRYPT);
    if (!TEST_mem_eq(&RC2cipher[n][0], 8, buf, 8))
        testresult = 0;

    RC2_ecb_encrypt(buf, buf2, &key, RC2_DECRYPT);
    if (!TEST_mem_eq(&RC2plain[n][0], 8, buf2, 8))
        testresult = 0;

    return testresult;
}