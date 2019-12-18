#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_C2I_ASN1_INTEGER ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_INTEGER_new () ; 
 scalar_t__ ASN1_STRING_set (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  V_ASN1_INTEGER ; 
 int /*<<< orphan*/  V_ASN1_NEG ; 
 size_t c2i_ibuf (int /*<<< orphan*/ *,int*,unsigned char const*,long) ; 

ASN1_INTEGER *c2i_ASN1_INTEGER(ASN1_INTEGER **a, const unsigned char **pp,
                               long len)
{
    ASN1_INTEGER *ret = NULL;
    size_t r;
    int neg;

    r = c2i_ibuf(NULL, NULL, *pp, len);

    if (r == 0)
        return NULL;

    if ((a == NULL) || ((*a) == NULL)) {
        ret = ASN1_INTEGER_new();
        if (ret == NULL)
            return NULL;
        ret->type = V_ASN1_INTEGER;
    } else
        ret = *a;

    if (ASN1_STRING_set(ret, NULL, r) == 0)
        goto err;

    c2i_ibuf(ret->data, &neg, *pp, len);

    if (neg)
        ret->type |= V_ASN1_NEG;

    *pp += len;
    if (a != NULL)
        (*a) = ret;
    return ret;
 err:
    ASN1err(ASN1_F_C2I_ASN1_INTEGER, ERR_R_MALLOC_FAILURE);
    if ((a == NULL) || (*a != ret))
        ASN1_INTEGER_free(ret);
    return NULL;
}