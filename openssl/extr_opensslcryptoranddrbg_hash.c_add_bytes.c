#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int seedlen; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int add_bytes(RAND_DRBG *drbg, unsigned char *dst,
                     unsigned char *in, size_t inlen)
{
    size_t i;
    int result;
    const unsigned char *add;
    unsigned char carry = 0, *d;

    assert(drbg->seedlen >= 1 && inlen >= 1 && inlen <= drbg->seedlen);

    d = &dst[drbg->seedlen - 1];
    add = &in[inlen - 1];

    for (i = inlen; i > 0; i--, d--, add--) {
        result = *d + *add + carry;
        carry = (unsigned char)(result >> 8);
        *d = (unsigned char)(result & 0xff);
    }

    if (carry != 0) {
        /* Add the carry to the top of the dst if inlen is not the same size */
        for (i = drbg->seedlen - inlen; i > 0; --i, d--) {
            *d += 1;     /* Carry can only be 1 */
            if (*d != 0) /* exit if carry doesnt propagate to the next byte */
                break;
        }
    }
    return 1;
}