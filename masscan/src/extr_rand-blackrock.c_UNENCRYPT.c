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
typedef  int uint64_t ;

/* Variables and functions */
 int READ (unsigned int,int,int) ; 

__attribute__((used)) static inline uint64_t
UNENCRYPT(unsigned r, uint64_t a, uint64_t b, uint64_t m, uint64_t seed)
{
    uint64_t L, R;
    unsigned j;
    uint64_t tmp;

    if (r & 1) {
        R = m % a;
        L = m / a;
    } else {
        L = m % a;
        R = m / a;
    }

    for (j=r; j>=1; j--) {
        if (j & 1) {
            tmp = READ(j, L, seed);
            if (tmp > R) {
                tmp = (tmp - R);
                tmp = a - (tmp%a);
                if (tmp == a)
                    tmp = 0;
            } else {
                tmp = (R - tmp);
                tmp %= a;
            }
        } else {
            tmp = READ(j, L, seed);
            if (tmp > R) {
                tmp = (tmp - R);
                tmp = b - (tmp%b);
                if (tmp == b)
                    tmp = 0;
            } else {
                tmp = (R - tmp);
                tmp %= b;
            }
        }
        R = L;
        L = tmp;
    }
    return a * R + L;
}