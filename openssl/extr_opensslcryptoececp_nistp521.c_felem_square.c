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
typedef  int uint128_t ;
typedef  int* largefelem ;
typedef  int* felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_scalar (int*,int* const,int) ; 

__attribute__((used)) static void felem_square(largefelem out, const felem in)
{
    felem inx2, inx4;
    felem_scalar(inx2, in, 2);
    felem_scalar(inx4, in, 4);

    /*-
     * We have many cases were we want to do
     *   in[x] * in[y] +
     *   in[y] * in[x]
     * This is obviously just
     *   2 * in[x] * in[y]
     * However, rather than do the doubling on the 128 bit result, we
     * double one of the inputs to the multiplication by reading from
     * |inx2|
     */

    out[0] = ((uint128_t) in[0]) * in[0];
    out[1] = ((uint128_t) in[0]) * inx2[1];
    out[2] = ((uint128_t) in[0]) * inx2[2] + ((uint128_t) in[1]) * in[1];
    out[3] = ((uint128_t) in[0]) * inx2[3] + ((uint128_t) in[1]) * inx2[2];
    out[4] = ((uint128_t) in[0]) * inx2[4] +
             ((uint128_t) in[1]) * inx2[3] + ((uint128_t) in[2]) * in[2];
    out[5] = ((uint128_t) in[0]) * inx2[5] +
             ((uint128_t) in[1]) * inx2[4] + ((uint128_t) in[2]) * inx2[3];
    out[6] = ((uint128_t) in[0]) * inx2[6] +
             ((uint128_t) in[1]) * inx2[5] +
             ((uint128_t) in[2]) * inx2[4] + ((uint128_t) in[3]) * in[3];
    out[7] = ((uint128_t) in[0]) * inx2[7] +
             ((uint128_t) in[1]) * inx2[6] +
             ((uint128_t) in[2]) * inx2[5] + ((uint128_t) in[3]) * inx2[4];
    out[8] = ((uint128_t) in[0]) * inx2[8] +
             ((uint128_t) in[1]) * inx2[7] +
             ((uint128_t) in[2]) * inx2[6] +
             ((uint128_t) in[3]) * inx2[5] + ((uint128_t) in[4]) * in[4];

    /*
     * The remaining limbs fall above 2^521, with the first falling at 2^522.
     * They correspond to locations one bit up from the limbs produced above
     * so we would have to multiply by two to align them. Again, rather than
     * operate on the 128-bit result, we double one of the inputs to the
     * multiplication. If we want to double for both this reason, and the
     * reason above, then we end up multiplying by four.
     */

    /* 9 */
    out[0] += ((uint128_t) in[1]) * inx4[8] +
              ((uint128_t) in[2]) * inx4[7] +
              ((uint128_t) in[3]) * inx4[6] + ((uint128_t) in[4]) * inx4[5];

    /* 10 */
    out[1] += ((uint128_t) in[2]) * inx4[8] +
              ((uint128_t) in[3]) * inx4[7] +
              ((uint128_t) in[4]) * inx4[6] + ((uint128_t) in[5]) * inx2[5];

    /* 11 */
    out[2] += ((uint128_t) in[3]) * inx4[8] +
              ((uint128_t) in[4]) * inx4[7] + ((uint128_t) in[5]) * inx4[6];

    /* 12 */
    out[3] += ((uint128_t) in[4]) * inx4[8] +
              ((uint128_t) in[5]) * inx4[7] + ((uint128_t) in[6]) * inx2[6];

    /* 13 */
    out[4] += ((uint128_t) in[5]) * inx4[8] + ((uint128_t) in[6]) * inx4[7];

    /* 14 */
    out[5] += ((uint128_t) in[6]) * inx4[8] + ((uint128_t) in[7]) * inx2[7];

    /* 15 */
    out[6] += ((uint128_t) in[7]) * inx4[8];

    /* 16 */
    out[7] += ((uint128_t) in[8]) * inx2[8];
}