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

/* Variables and functions */
 int /*<<< orphan*/  twos_complement (unsigned char*,unsigned char const*,size_t,unsigned char) ; 

__attribute__((used)) static size_t i2c_ibuf(const unsigned char *b, size_t blen, int neg,
                       unsigned char **pp)
{
    unsigned int pad = 0;
    size_t ret, i;
    unsigned char *p, pb = 0;

    if (b != NULL && blen) {
        ret = blen;
        i = b[0];
        if (!neg && (i > 127)) {
            pad = 1;
            pb = 0;
        } else if (neg) {
            pb = 0xFF;
            if (i > 128) {
                pad = 1;
            } else if (i == 128) {
                /*
                 * Special case [of minimal negative for given length]:
                 * if any other bytes non zero we pad, otherwise we don't.
                 */
                for (pad = 0, i = 1; i < blen; i++)
                    pad |= b[i];
                pb = pad != 0 ? 0xffU : 0;
                pad = pb & 1;
            }
        }
        ret += pad;
    } else {
        ret = 1;
        blen = 0;   /* reduce '(b == NULL || blen == 0)' to '(blen == 0)' */
    }

    if (pp == NULL || (p = *pp) == NULL)
        return ret;

    /*
     * This magically handles all corner cases, such as '(b == NULL ||
     * blen == 0)', non-negative value, "negative" zero, 0x80 followed
     * by any number of zeros...
     */
    *p = pb;
    p += pad;       /* yes, p[0] can be written twice, but it's little
                     * price to pay for eliminated branches */
    twos_complement(p, b, blen, pb);

    *pp += ret;
    return ret;
}