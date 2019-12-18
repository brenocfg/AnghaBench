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
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TEST_mem_eq (unsigned char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ ** data ; 
 scalar_t__* data_len ; 
 int /*<<< orphan*/ ** keys ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * output ; 

__attribute__((used)) static int test_rc4_encrypt(const int i)
{
    unsigned char obuf[512];
    RC4_KEY key;

    RC4_set_key(&key, keys[i][0], &(keys[i][1]));
    memset(obuf, 0, sizeof(obuf));
    RC4(&key, data_len[i], &(data[i][0]), obuf);
    return TEST_mem_eq(obuf, data_len[i] + 1, output[i], data_len[i] + 1);
}