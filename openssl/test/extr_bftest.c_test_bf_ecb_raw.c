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
typedef  int /*<<< orphan*/  BF_LONG ;
typedef  int /*<<< orphan*/  BF_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BF_BLOCK ; 
 int /*<<< orphan*/  BF_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BF_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BF_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** bf_cipher ; 
 scalar_t__* bf_key ; 
 int /*<<< orphan*/ ** bf_plain ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static int test_bf_ecb_raw(int n)
{
    int ret = 1;
    BF_KEY key;
    BF_LONG data[2];

    BF_set_key(&key, strlen(bf_key[n]), (unsigned char *)bf_key[n]);

    data[0] = bf_plain[n][0];
    data[1] = bf_plain[n][1];
    BF_encrypt(data, &key);
    if (!TEST_mem_eq(&(bf_cipher[n][0]), BF_BLOCK, &(data[0]), BF_BLOCK))
        ret = 0;

    BF_decrypt(&(data[0]), &key);
    if (!TEST_mem_eq(&(bf_plain[n][0]), BF_BLOCK, &(data[0]), BF_BLOCK))
        ret = 0;

    return ret;
}