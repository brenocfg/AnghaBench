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
typedef  int /*<<< orphan*/  longfelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void felem_inv(felem out, const felem in)
{
    felem ftmp, ftmp2;
    /* each e_I will hold |in|^{2^I - 1} */
    felem e2, e4, e8, e16, e32, e64;
    longfelem tmp;
    unsigned i;

    felem_square(tmp, in);
    felem_reduce(ftmp, tmp);    /* 2^1 */
    felem_mul(tmp, in, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^2 - 2^0 */
    felem_assign(e2, ftmp);
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^3 - 2^1 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^4 - 2^2 */
    felem_mul(tmp, ftmp, e2);
    felem_reduce(ftmp, tmp);    /* 2^4 - 2^0 */
    felem_assign(e4, ftmp);
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^5 - 2^1 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^6 - 2^2 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^7 - 2^3 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^8 - 2^4 */
    felem_mul(tmp, ftmp, e4);
    felem_reduce(ftmp, tmp);    /* 2^8 - 2^0 */
    felem_assign(e8, ftmp);
    for (i = 0; i < 8; i++) {
        felem_square(tmp, ftmp);
        felem_reduce(ftmp, tmp);
    }                           /* 2^16 - 2^8 */
    felem_mul(tmp, ftmp, e8);
    felem_reduce(ftmp, tmp);    /* 2^16 - 2^0 */
    felem_assign(e16, ftmp);
    for (i = 0; i < 16; i++) {
        felem_square(tmp, ftmp);
        felem_reduce(ftmp, tmp);
    }                           /* 2^32 - 2^16 */
    felem_mul(tmp, ftmp, e16);
    felem_reduce(ftmp, tmp);    /* 2^32 - 2^0 */
    felem_assign(e32, ftmp);
    for (i = 0; i < 32; i++) {
        felem_square(tmp, ftmp);
        felem_reduce(ftmp, tmp);
    }                           /* 2^64 - 2^32 */
    felem_assign(e64, ftmp);
    felem_mul(tmp, ftmp, in);
    felem_reduce(ftmp, tmp);    /* 2^64 - 2^32 + 2^0 */
    for (i = 0; i < 192; i++) {
        felem_square(tmp, ftmp);
        felem_reduce(ftmp, tmp);
    }                           /* 2^256 - 2^224 + 2^192 */

    felem_mul(tmp, e64, e32);
    felem_reduce(ftmp2, tmp);   /* 2^64 - 2^0 */
    for (i = 0; i < 16; i++) {
        felem_square(tmp, ftmp2);
        felem_reduce(ftmp2, tmp);
    }                           /* 2^80 - 2^16 */
    felem_mul(tmp, ftmp2, e16);
    felem_reduce(ftmp2, tmp);   /* 2^80 - 2^0 */
    for (i = 0; i < 8; i++) {
        felem_square(tmp, ftmp2);
        felem_reduce(ftmp2, tmp);
    }                           /* 2^88 - 2^8 */
    felem_mul(tmp, ftmp2, e8);
    felem_reduce(ftmp2, tmp);   /* 2^88 - 2^0 */
    for (i = 0; i < 4; i++) {
        felem_square(tmp, ftmp2);
        felem_reduce(ftmp2, tmp);
    }                           /* 2^92 - 2^4 */
    felem_mul(tmp, ftmp2, e4);
    felem_reduce(ftmp2, tmp);   /* 2^92 - 2^0 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^93 - 2^1 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^94 - 2^2 */
    felem_mul(tmp, ftmp2, e2);
    felem_reduce(ftmp2, tmp);   /* 2^94 - 2^0 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^95 - 2^1 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^96 - 2^2 */
    felem_mul(tmp, ftmp2, in);
    felem_reduce(ftmp2, tmp);   /* 2^96 - 3 */

    felem_mul(tmp, ftmp2, ftmp);
    felem_reduce(out, tmp);     /* 2^256 - 2^224 + 2^192 + 2^96 - 3 */
}