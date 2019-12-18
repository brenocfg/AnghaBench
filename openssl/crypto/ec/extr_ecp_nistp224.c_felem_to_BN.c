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
 int /*<<< orphan*/ * BN_lebin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  felem_to_bin28 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static BIGNUM *felem_to_BN(BIGNUM *out, const felem in)
{
    felem_bytearray b_out;
    felem_to_bin28(b_out, in);
    return BN_lebin2bn(b_out, sizeof(b_out), out);
}