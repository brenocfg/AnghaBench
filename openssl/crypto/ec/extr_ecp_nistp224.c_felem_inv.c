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
typedef  int /*<<< orphan*/  widefelem ;
typedef  int /*<<< orphan*/  const felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_mul (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void felem_inv(felem out, const felem in)
{
    felem ftmp, ftmp2, ftmp3, ftmp4;
    widefelem tmp;
    unsigned i;

    felem_square(tmp, in);
    felem_reduce(ftmp, tmp);    /* 2 */
    felem_mul(tmp, in, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^2 - 1 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^3 - 2 */
    felem_mul(tmp, in, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^3 - 1 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp2, tmp);   /* 2^4 - 2 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^5 - 4 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^6 - 8 */
    felem_mul(tmp, ftmp2, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^6 - 1 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp2, tmp);   /* 2^7 - 2 */
    for (i = 0; i < 5; ++i) {   /* 2^12 - 2^6 */
        felem_square(tmp, ftmp2);
        felem_reduce(ftmp2, tmp);
    }
    felem_mul(tmp, ftmp2, ftmp);
    felem_reduce(ftmp2, tmp);   /* 2^12 - 1 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^13 - 2 */
    for (i = 0; i < 11; ++i) {  /* 2^24 - 2^12 */
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp);
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp2, tmp);   /* 2^24 - 1 */
    felem_square(tmp, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^25 - 2 */
    for (i = 0; i < 23; ++i) {  /* 2^48 - 2^24 */
        felem_square(tmp, ftmp3);
        felem_reduce(ftmp3, tmp);
    }
    felem_mul(tmp, ftmp3, ftmp2);
    felem_reduce(ftmp3, tmp);   /* 2^48 - 1 */
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp4, tmp);   /* 2^49 - 2 */
    for (i = 0; i < 47; ++i) {  /* 2^96 - 2^48 */
        felem_square(tmp, ftmp4);
        felem_reduce(ftmp4, tmp);
    }
    felem_mul(tmp, ftmp3, ftmp4);
    felem_reduce(ftmp3, tmp);   /* 2^96 - 1 */
    felem_square(tmp, ftmp3);
    felem_reduce(ftmp4, tmp);   /* 2^97 - 2 */
    for (i = 0; i < 23; ++i) {  /* 2^120 - 2^24 */
        felem_square(tmp, ftmp4);
        felem_reduce(ftmp4, tmp);
    }
    felem_mul(tmp, ftmp2, ftmp4);
    felem_reduce(ftmp2, tmp);   /* 2^120 - 1 */
    for (i = 0; i < 6; ++i) {   /* 2^126 - 2^6 */
        felem_square(tmp, ftmp2);
        felem_reduce(ftmp2, tmp);
    }
    felem_mul(tmp, ftmp2, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^126 - 1 */
    felem_square(tmp, ftmp);
    felem_reduce(ftmp, tmp);    /* 2^127 - 2 */
    felem_mul(tmp, ftmp, in);
    felem_reduce(ftmp, tmp);    /* 2^127 - 1 */
    for (i = 0; i < 97; ++i) {  /* 2^224 - 2^97 */
        felem_square(tmp, ftmp);
        felem_reduce(ftmp, tmp);
    }
    felem_mul(tmp, ftmp, ftmp3);
    felem_reduce(out, tmp);     /* 2^224 - 2^96 - 1 */
}