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
typedef  int /*<<< orphan*/  smallfelem ;
typedef  int /*<<< orphan*/  felem_bytearray ;
typedef  int /*<<< orphan*/  b_out ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flip_endian (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smallfelem_to_bin32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static BIGNUM *smallfelem_to_BN(BIGNUM *out, const smallfelem in)
{
    felem_bytearray b_in, b_out;
    smallfelem_to_bin32(b_in, in);
    flip_endian(b_out, b_in, sizeof(b_out));
    return BN_bin2bn(b_out, sizeof(b_out), out);
}