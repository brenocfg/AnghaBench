#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; unsigned char* data; int length; } ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_D2I_ASN1_UINTEGER ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_INTEGER_new () ; 
 int ASN1_R_BAD_OBJECT_HEADER ; 
 int ASN1_R_EXPECTING_AN_INTEGER ; 
 int ASN1_get_object (unsigned char const**,long*,int*,int*,long) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int) ; 
 int ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int V_ASN1_INTEGER ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

ASN1_INTEGER *d2i_ASN1_UINTEGER(ASN1_INTEGER **a, const unsigned char **pp,
                                long length)
{
    ASN1_INTEGER *ret = NULL;
    const unsigned char *p;
    unsigned char *s;
    long len;
    int inf, tag, xclass;
    int i;

    if ((a == NULL) || ((*a) == NULL)) {
        if ((ret = ASN1_INTEGER_new()) == NULL)
            return NULL;
        ret->type = V_ASN1_INTEGER;
    } else
        ret = (*a);

    p = *pp;
    inf = ASN1_get_object(&p, &len, &tag, &xclass, length);
    if (inf & 0x80) {
        i = ASN1_R_BAD_OBJECT_HEADER;
        goto err;
    }

    if (tag != V_ASN1_INTEGER) {
        i = ASN1_R_EXPECTING_AN_INTEGER;
        goto err;
    }

    /*
     * We must OPENSSL_malloc stuff, even for 0 bytes otherwise it signifies
     * a missing NULL parameter.
     */
    s = OPENSSL_malloc((int)len + 1);
    if (s == NULL) {
        i = ERR_R_MALLOC_FAILURE;
        goto err;
    }
    ret->type = V_ASN1_INTEGER;
    if (len) {
        if ((*p == 0) && (len != 1)) {
            p++;
            len--;
        }
        memcpy(s, p, (int)len);
        p += len;
    }

    OPENSSL_free(ret->data);
    ret->data = s;
    ret->length = (int)len;
    if (a != NULL)
        (*a) = ret;
    *pp = p;
    return ret;
 err:
    ASN1err(ASN1_F_D2I_ASN1_UINTEGER, i);
    if ((a == NULL) || (*a != ret))
        ASN1_INTEGER_free(ret);
    return NULL;
}