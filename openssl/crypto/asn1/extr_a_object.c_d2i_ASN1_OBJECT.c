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
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_D2I_ASN1_OBJECT ; 
 int ASN1_R_BAD_OBJECT_HEADER ; 
 int ASN1_R_EXPECTING_AN_OBJECT ; 
 int ASN1_get_object (unsigned char const**,long*,int*,int*,long) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int) ; 
 int V_ASN1_OBJECT ; 
 int /*<<< orphan*/ * c2i_ASN1_OBJECT (int /*<<< orphan*/ **,unsigned char const**,long) ; 

ASN1_OBJECT *d2i_ASN1_OBJECT(ASN1_OBJECT **a, const unsigned char **pp,
                             long length)
{
    const unsigned char *p;
    long len;
    int tag, xclass;
    int inf, i;
    ASN1_OBJECT *ret = NULL;
    p = *pp;
    inf = ASN1_get_object(&p, &len, &tag, &xclass, length);
    if (inf & 0x80) {
        i = ASN1_R_BAD_OBJECT_HEADER;
        goto err;
    }

    if (tag != V_ASN1_OBJECT) {
        i = ASN1_R_EXPECTING_AN_OBJECT;
        goto err;
    }
    ret = c2i_ASN1_OBJECT(a, &p, len);
    if (ret)
        *pp = p;
    return ret;
 err:
    ASN1err(ASN1_F_D2I_ASN1_OBJECT, i);
    return NULL;
}