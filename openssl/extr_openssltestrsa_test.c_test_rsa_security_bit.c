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
typedef  int /*<<< orphan*/  num ;
struct TYPE_2__ {int bits; int r; } ;
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  RSA_security_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_le (int const,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_uint_eq (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char const,int const) ; 
 TYPE_1__* rsa_security_bits_cases ; 

__attribute__((used)) static int test_rsa_security_bit(int n)
{
    static const unsigned char vals[8] = {
        0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40
    };
    RSA *key = RSA_new();
    const int bits = rsa_security_bits_cases[n].bits;
    const int result = rsa_security_bits_cases[n].r;
    const int bytes = (bits + 7) / 8;
    int r = 0;
    unsigned char num[2000];

    if (!TEST_ptr(key) || !TEST_int_le(bytes, (int)sizeof(num)))
        goto err;

    /*
     * It is necessary to set the RSA key in order to ask for the strength.
     * A BN of an appropriate size is created, in general it won't have the
     * properties necessary for RSA to function.  This is okay here since
     * the RSA key is never used.
     */
    memset(num, vals[bits % 8], bytes);

    /*
     * The 'e' parameter is set to the same value as 'n'.  This saves having
     * an extra BN to hold a sensible value for 'e'.  This is safe since the
     * RSA key is not used.  The 'd' parameter can be NULL safely.
     */
    if (TEST_true(RSA_set0_key(key, BN_bin2bn(num, bytes, NULL),
                               BN_bin2bn(num, bytes, NULL), NULL))
            && TEST_uint_eq(RSA_security_bits(key), result))
        r = 1;
err:
    RSA_free(key);
    return r;
}