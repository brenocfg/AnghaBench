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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_OUTPUT_SIZE ; 
 int BN_bn2bin (int /*<<< orphan*/  const*,unsigned char*) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hex_convert_memory (unsigned char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_bignum_zero_null (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_fail_bignum_common (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_printf_stderr (char*,char const*,char*,...) ; 

void test_output_bignum(const char *name, const BIGNUM *bn)
{
    if (bn == NULL || BN_is_zero(bn)) {
        test_printf_stderr("bignum: '%s' = %s\n", name,
                           test_bignum_zero_null(bn));
    } else if (BN_num_bytes(bn) <= BN_OUTPUT_SIZE) {
        unsigned char buf[BN_OUTPUT_SIZE];
        char out[2 * sizeof(buf) + 1];
        char *p = out;
        int n = BN_bn2bin(bn, buf);

        hex_convert_memory(buf, n, p, BN_OUTPUT_SIZE);
        while (*p == '0' && *++p != '\0')
            ;
        test_printf_stderr("bignum: '%s' = %s0x%s\n", name,
                           BN_is_negative(bn) ? "-" : "", p);
    } else {
        test_fail_bignum_common("bignum", NULL, 0, NULL, NULL, NULL, name,
                                bn, bn);
    }
}