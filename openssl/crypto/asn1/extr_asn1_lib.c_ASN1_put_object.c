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
 int V_ASN1_CONSTRUCTED ; 
 int V_ASN1_PRIMITIVE_TAG ; 
 int V_ASN1_PRIVATE ; 
 int /*<<< orphan*/  asn1_put_length (unsigned char**,int) ; 

void ASN1_put_object(unsigned char **pp, int constructed, int length, int tag,
                     int xclass)
{
    unsigned char *p = *pp;
    int i, ttag;

    i = (constructed) ? V_ASN1_CONSTRUCTED : 0;
    i |= (xclass & V_ASN1_PRIVATE);
    if (tag < 31)
        *(p++) = i | (tag & V_ASN1_PRIMITIVE_TAG);
    else {
        *(p++) = i | V_ASN1_PRIMITIVE_TAG;
        for (i = 0, ttag = tag; ttag > 0; i++)
            ttag >>= 7;
        ttag = i;
        while (i-- > 0) {
            p[i] = tag & 0x7f;
            if (i != (ttag - 1))
                p[i] |= 0x80;
            tag >>= 7;
        }
        p += ttag;
    }
    if (constructed == 2)
        *(p++) = 0x80;
    else
        asn1_put_length(&p, length);
    *pp = p;
}