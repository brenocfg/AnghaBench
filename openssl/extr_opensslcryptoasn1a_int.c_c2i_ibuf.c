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
 int /*<<< orphan*/  ASN1_F_C2I_IBUF ; 
 int /*<<< orphan*/  ASN1_R_ILLEGAL_PADDING ; 
 int /*<<< orphan*/  ASN1_R_ILLEGAL_ZERO_CONTENT ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twos_complement (unsigned char*,unsigned char const*,size_t,int) ; 

__attribute__((used)) static size_t c2i_ibuf(unsigned char *b, int *pneg,
                       const unsigned char *p, size_t plen)
{
    int neg, pad;
    /* Zero content length is illegal */
    if (plen == 0) {
        ASN1err(ASN1_F_C2I_IBUF, ASN1_R_ILLEGAL_ZERO_CONTENT);
        return 0;
    }
    neg = p[0] & 0x80;
    if (pneg)
        *pneg = neg;
    /* Handle common case where length is 1 octet separately */
    if (plen == 1) {
        if (b != NULL) {
            if (neg)
                b[0] = (p[0] ^ 0xFF) + 1;
            else
                b[0] = p[0];
        }
        return 1;
    }

    pad = 0;
    if (p[0] == 0) {
        pad = 1;
    } else if (p[0] == 0xFF) {
        size_t i;

        /*
         * Special case [of "one less minimal negative" for given length]:
         * if any other bytes non zero it was padded, otherwise not.
         */
        for (pad = 0, i = 1; i < plen; i++)
            pad |= p[i];
        pad = pad != 0 ? 1 : 0;
    }
    /* reject illegal padding: first two octets MSB can't match */
    if (pad && (neg == (p[1] & 0x80))) {
        ASN1err(ASN1_F_C2I_IBUF, ASN1_R_ILLEGAL_PADDING);
        return 0;
    }

    /* skip over pad */
    p += pad;
    plen -= pad;

    if (b != NULL)
        twos_complement(b, p, plen, neg ? 0xffU : 0);

    return plen;
}