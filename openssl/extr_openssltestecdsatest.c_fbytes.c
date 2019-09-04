#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* bytes ) (unsigned char*,int) ;} ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2binpad (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_num_bytes (int /*<<< orphan*/ *) ; 
 int OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_lt (int,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * numbers ; 
 TYPE_1__* old_rand ; 
 int stub1 (unsigned char*,int) ; 
 scalar_t__ use_fake ; 

__attribute__((used)) static int fbytes(unsigned char *buf, int num)
{
    int ret = 0;
    static int fbytes_counter = 0;
    BIGNUM *tmp = NULL;

    if (use_fake == 0)
        return old_rand->bytes(buf, num);

    use_fake = 0;

    if (!TEST_ptr(tmp = BN_new())
        || !TEST_int_lt(fbytes_counter, OSSL_NELEM(numbers))
        || !TEST_true(BN_hex2bn(&tmp, numbers[fbytes_counter]))
        /* tmp might need leading zeros so pad it out */
        || !TEST_int_le(BN_num_bytes(tmp), num)
        || !TEST_true(BN_bn2binpad(tmp, buf, num)))
        goto err;

    fbytes_counter = (fbytes_counter + 1) % OSSL_NELEM(numbers);
    ret = 1;
 err:
    BN_free(tmp);
    return ret;
}