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
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  AES_set_encrypt_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cts128_test_key ; 

__attribute__((used)) static AES_KEY *cts128_encrypt_key_schedule(void)
{
    static int init_key = 1;
    static AES_KEY ks;

    if (init_key) {
        AES_set_encrypt_key(cts128_test_key, 128, &ks);
        init_key = 0;
    }
    return &ks;
}