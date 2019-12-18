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
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  RC4_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int const,int /*<<< orphan*/ ,int const) ; 
 int TEST_uchar_eq (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** data ; 
 int /*<<< orphan*/ ** keys ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * output ; 

__attribute__((used)) static int test_rc4_end_processing(const int i)
{
    unsigned char obuf[512];
    RC4_KEY key;

    RC4_set_key(&key, keys[3][0], &(keys[3][1]));
    memset(obuf, 0, sizeof(obuf));
    RC4(&key, i, &(data[3][0]), obuf);
    if (!TEST_mem_eq(obuf, i, output[3], i))
        return 0;
    return TEST_uchar_eq(obuf[i], 0);
}