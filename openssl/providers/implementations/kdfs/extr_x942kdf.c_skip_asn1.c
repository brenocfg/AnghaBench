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
 int ASN1_get_object (unsigned char const**,long*,int*,int*,long) ; 
 int V_ASN1_OBJECT ; 
 int V_ASN1_UNIVERSAL ; 

__attribute__((used)) static int skip_asn1(unsigned char **pp, long *plen, int exptag)
{
    int i, tag, xclass;
    long tmplen;
    const unsigned char *q = *pp;

    i = ASN1_get_object(&q, &tmplen, &tag, &xclass, *plen);
    if ((i & 0x80) != 0 || tag != exptag || xclass != V_ASN1_UNIVERSAL)
        return 0;
    if (tag == V_ASN1_OBJECT)
        q += tmplen;
    *pp = (unsigned char *)q;
    *plen -= q - *pp;
    return 1;
}