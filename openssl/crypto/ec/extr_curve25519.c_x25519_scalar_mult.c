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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  fe51 ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int*,int) ; 
 int /*<<< orphan*/  fe51_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_cswap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  fe51_frombytes (int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  fe51_invert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_mul121666 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe51_tobytes (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 scalar_t__ x25519_fe64_eligible () ; 
 int /*<<< orphan*/  x25519_scalar_mulx (int*,int const*,int const*) ; 

__attribute__((used)) static void x25519_scalar_mult(uint8_t out[32], const uint8_t scalar[32],
                               const uint8_t point[32])
{
    fe51 x1, x2, z2, x3, z3, tmp0, tmp1;
    uint8_t e[32];
    unsigned swap = 0;
    int pos;

# ifdef BASE_2_64_IMPLEMENTED
    if (x25519_fe64_eligible()) {
        x25519_scalar_mulx(out, scalar, point);
        return;
    }
# endif

    memcpy(e, scalar, 32);
    e[0]  &= 0xf8;
    e[31] &= 0x7f;
    e[31] |= 0x40;
    fe51_frombytes(x1, point);
    fe51_1(x2);
    fe51_0(z2);
    fe51_copy(x3, x1);
    fe51_1(z3);

    for (pos = 254; pos >= 0; --pos) {
        unsigned int b = 1 & (e[pos / 8] >> (pos & 7));

        swap ^= b;
        fe51_cswap(x2, x3, swap);
        fe51_cswap(z2, z3, swap);
        swap = b;
        fe51_sub(tmp0, x3, z3);
        fe51_sub(tmp1, x2, z2);
        fe51_add(x2, x2, z2);
        fe51_add(z2, x3, z3);
        fe51_mul(z3, tmp0, x2);
        fe51_mul(z2, z2, tmp1);
        fe51_sq(tmp0, tmp1);
        fe51_sq(tmp1, x2);
        fe51_add(x3, z3, z2);
        fe51_sub(z2, z3, z2);
        fe51_mul(x2, tmp1, tmp0);
        fe51_sub(tmp1, tmp1, tmp0);
        fe51_sq(z2, z2);
        fe51_mul121666(z3, tmp1);
        fe51_sq(x3, x3);
        fe51_add(tmp0, tmp0, z3);
        fe51_mul(z3, x1, z2);
        fe51_mul(z2, tmp1, tmp0);
    }

    fe51_invert(z2, z2);
    fe51_mul(x2, x2, z2);
    fe51_tobytes(out, x2);

    OPENSSL_cleanse(e, sizeof(e));
}