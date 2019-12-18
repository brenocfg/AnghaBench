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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_is_odd (int /*<<< orphan*/  const*) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 

int rsa_check_public_exponent(const BIGNUM *e)
{
    int bitlen = BN_num_bits(e);

    return (BN_is_odd(e) &&  bitlen > 16 && bitlen < 257);
}