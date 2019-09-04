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
typedef  int /*<<< orphan*/  felem_bytearray ;
typedef  int /*<<< orphan*/  felem ;
typedef  int /*<<< orphan*/  b_out ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 unsigned int BN_bn2bin (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 unsigned int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_BN_TO_FELEM ; 
 int /*<<< orphan*/  EC_R_BIGNUM_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin66_to_felem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flip_endian (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int BN_to_felem(felem out, const BIGNUM *bn)
{
    felem_bytearray b_in;
    felem_bytearray b_out;
    unsigned num_bytes;

    /* BN_bn2bin eats leading zeroes */
    memset(b_out, 0, sizeof(b_out));
    num_bytes = BN_num_bytes(bn);
    if (num_bytes > sizeof(b_out)) {
        ECerr(EC_F_BN_TO_FELEM, EC_R_BIGNUM_OUT_OF_RANGE);
        return 0;
    }
    if (BN_is_negative(bn)) {
        ECerr(EC_F_BN_TO_FELEM, EC_R_BIGNUM_OUT_OF_RANGE);
        return 0;
    }
    num_bytes = BN_bn2bin(bn, b_in);
    flip_endian(b_out, b_in, num_bytes);
    bin66_to_felem(out, b_out);
    return 1;
}