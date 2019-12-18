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
typedef  int /*<<< orphan*/  largefelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void felem_inv(felem out, const felem in)
{
    felem ftmp, ftmp2, ftmp3, ftmp4;
    largefelem tmp;
    unsigned i;

    felem_square(tmp, in);
    felem_reduce(ftmp, tmp);    /* 2^1 */
    felem_mul(tmp, in, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^2 - 2^0 */
    felem_assign(ftmp2, ftmp);
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^3 - 2^1 */
    felem_mul(tmp, in, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^3 - 2^0 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^4 - 2^1 */

    felem_square(tmp, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^3 - 2^1 */
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp3, tmp);   /* 2^4 - 2^2 */
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^4 - 2^0 */

    felem_assign(ftmp2, ftmp3);
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp3, tmp);   /* 2^5 - 2^1 */
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp3, tmp);   /* 2^6 - 2^2 */
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp3, tmp);   /* 2^7 - 2^3 */
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp3, tmp);   /* 2^8 - 2^4 */
    felem_assign(ftmp4, ftmp3);
    felem_mul(tmp, ftmp3, ftmp);
    felem_reduce(ftmp4, tmp);   /* 2^8 - 2^1 */
    felem_square(tmp, ftmp4);
    felem_reduce(ftmp4, tmp);   /* 2^9 - 2^2 */
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^8 - 2^0 */
    felem_assign(ftmp2, ftmp3);

    for (i = 0; i < 8; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^16 - 2^8 */
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^16 - 2^0 */
    felem_assign(ftmp2, ftmp3);

    for (i = 0; i < 16; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^32 - 2^16 */
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^32 - 2^0 */
    felem_assign(ftmp2, ftmp3);

    for (i = 0; i < 32; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^64 - 2^32 */
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^64 - 2^0 */
    felem_assign(ftmp2, ftmp3);

    for (i = 0; i < 64; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^128 - 2^64 */
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^128 - 2^0 */
    felem_assign(ftmp2, ftmp3);

    for (i = 0; i < 128; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^256 - 2^128 */
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^256 - 2^0 */
    felem_assign(ftmp2, ftmp3);

    for (i = 0; i < 256; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^512 - 2^256 */
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^512 - 2^0 */

    for (i = 0; i < 9; i++) {
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp); /* 2^521 - 2^9 */
    }
    felem_mul(tmp, ftmp3, ftmp4);
    felem_reduce(ftmp3, tmp);   /* 2^512 - 2^2 */
    felem_mul(tmp, ftmp3, in);
    felem_reduce(out, tmp);     /* 2^512 - 3 */
}