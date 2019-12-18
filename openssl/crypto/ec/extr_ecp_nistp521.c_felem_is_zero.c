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
typedef  int limb ;
typedef  int* felem ;

/* Variables and functions */
 int bottom57bits ; 
 int bottom58bits ; 
 int /*<<< orphan*/  felem_assign (int*,int* const) ; 
 int* kPrime ; 

__attribute__((used)) static limb felem_is_zero(const felem in)
{
    felem ftmp;
    limb is_zero, is_p;
    felem_assign(ftmp, in);

    ftmp[0] += ftmp[8] >> 57;
    ftmp[8] &= bottom57bits;
    /* ftmp[8] < 2^57 */
    ftmp[1] += ftmp[0] >> 58;
    ftmp[0] &= bottom58bits;
    ftmp[2] += ftmp[1] >> 58;
    ftmp[1] &= bottom58bits;
    ftmp[3] += ftmp[2] >> 58;
    ftmp[2] &= bottom58bits;
    ftmp[4] += ftmp[3] >> 58;
    ftmp[3] &= bottom58bits;
    ftmp[5] += ftmp[4] >> 58;
    ftmp[4] &= bottom58bits;
    ftmp[6] += ftmp[5] >> 58;
    ftmp[5] &= bottom58bits;
    ftmp[7] += ftmp[6] >> 58;
    ftmp[6] &= bottom58bits;
    ftmp[8] += ftmp[7] >> 58;
    ftmp[7] &= bottom58bits;
    /* ftmp[8] < 2^57 + 4 */

    /*
     * The ninth limb of 2*(2^521-1) is 0x03ffffffffffffff, which is greater
     * than our bound for ftmp[8]. Therefore we only have to check if the
     * zero is zero or 2^521-1.
     */

    is_zero = 0;
    is_zero |= ftmp[0];
    is_zero |= ftmp[1];
    is_zero |= ftmp[2];
    is_zero |= ftmp[3];
    is_zero |= ftmp[4];
    is_zero |= ftmp[5];
    is_zero |= ftmp[6];
    is_zero |= ftmp[7];
    is_zero |= ftmp[8];

    is_zero--;
    /*
     * We know that ftmp[i] < 2^63, therefore the only way that the top bit
     * can be set is if is_zero was 0 before the decrement.
     */
    is_zero = 0 - (is_zero >> 63);

    is_p = ftmp[0] ^ kPrime[0];
    is_p |= ftmp[1] ^ kPrime[1];
    is_p |= ftmp[2] ^ kPrime[2];
    is_p |= ftmp[3] ^ kPrime[3];
    is_p |= ftmp[4] ^ kPrime[4];
    is_p |= ftmp[5] ^ kPrime[5];
    is_p |= ftmp[6] ^ kPrime[6];
    is_p |= ftmp[7] ^ kPrime[7];
    is_p |= ftmp[8] ^ kPrime[8];

    is_p--;
    is_p = 0 - (is_p >> 63);

    is_zero |= is_p;
    return is_zero;
}