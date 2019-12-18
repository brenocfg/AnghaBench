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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (int*,int*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int*,int) ; 
 int /*<<< orphan*/  do_xor (int*,int*,int) ; 
 int /*<<< orphan*/  galois_divpower (int*,int,int) ; 
 int /*<<< orphan*/  galois_double (int*,int) ; 
 int gdiv (int,int) ; 
 int gmul (int,int) ; 
 int gpow2 (int) ; 

void raid6_recover2(uint8_t* sectors, uint16_t num_stripes, ULONG sector_size, uint16_t missing1, uint16_t missing2, uint8_t* out) {
    if (missing1 == num_stripes - 2 || missing2 == num_stripes - 2) { // reconstruct from q and data
        uint16_t missing = missing1 == (num_stripes - 2) ? missing2 : missing1;
        uint16_t stripe;

        stripe = num_stripes - 3;

        if (stripe == missing)
            RtlZeroMemory(out, sector_size);
        else
            RtlCopyMemory(out, sectors + (stripe * sector_size), sector_size);

        do {
            stripe--;

            galois_double(out, sector_size);

            if (stripe != missing)
                do_xor(out, sectors + (stripe * sector_size), sector_size);
        } while (stripe > 0);

        do_xor(out, sectors + ((num_stripes - 1) * sector_size), sector_size);

        if (missing != 0)
            galois_divpower(out, (uint8_t)missing, sector_size);
    } else { // reconstruct from p and q
        uint16_t x, y, stripe;
        uint8_t gyx, gx, denom, a, b, *p, *q, *pxy, *qxy;
        uint32_t j;

        stripe = num_stripes - 3;

        pxy = out + sector_size;
        qxy = out;

        if (stripe == missing1 || stripe == missing2) {
            RtlZeroMemory(qxy, sector_size);
            RtlZeroMemory(pxy, sector_size);

            if (stripe == missing1)
                x = stripe;
            else
                y = stripe;
        } else {
            RtlCopyMemory(qxy, sectors + (stripe * sector_size), sector_size);
            RtlCopyMemory(pxy, sectors + (stripe * sector_size), sector_size);
        }

        do {
            stripe--;

            galois_double(qxy, sector_size);

            if (stripe != missing1 && stripe != missing2) {
                do_xor(qxy, sectors + (stripe * sector_size), sector_size);
                do_xor(pxy, sectors + (stripe * sector_size), sector_size);
            } else if (stripe == missing1)
                x = stripe;
            else if (stripe == missing2)
                y = stripe;
        } while (stripe > 0);

        gyx = gpow2(y > x ? (y-x) : (255-x+y));
        gx = gpow2(255-x);

        denom = gdiv(1, gyx ^ 1);
        a = gmul(gyx, denom);
        b = gmul(gx, denom);

        p = sectors + ((num_stripes - 2) * sector_size);
        q = sectors + ((num_stripes - 1) * sector_size);

        for (j = 0; j < sector_size; j++) {
            *qxy = gmul(a, *p ^ *pxy) ^ gmul(b, *q ^ *qxy);

            p++;
            q++;
            pxy++;
            qxy++;
        }

        do_xor(out + sector_size, out, sector_size);
        do_xor(out + sector_size, sectors + ((num_stripes - 2) * sector_size), sector_size);
    }
}