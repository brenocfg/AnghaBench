#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ itype; int utype; int size; TYPE_3__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* prim_free ) (int /*<<< orphan*/ **,TYPE_4__ const*) ;int /*<<< orphan*/  (* prim_clear ) (int /*<<< orphan*/ **,TYPE_4__ const*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * asn1_value; } ;
struct TYPE_9__ {int type; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_2__ ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_STRING ;
typedef  TYPE_3__ ASN1_PRIMITIVE_FUNCS ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  TYPE_4__ ASN1_ITEM ;
typedef  int ASN1_BOOLEAN ;

/* Variables and functions */
 scalar_t__ ASN1_ITYPE_MSTRING ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
#define  V_ASN1_ANY 131 
#define  V_ASN1_BOOLEAN 130 
#define  V_ASN1_NULL 129 
#define  V_ASN1_OBJECT 128 
 int /*<<< orphan*/  asn1_string_embed_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_4__ const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ **,TYPE_4__ const*) ; 

void asn1_primitive_free(ASN1_VALUE **pval, const ASN1_ITEM *it, int embed)
{
    int utype;

    /* Special case: if 'it' is a primitive with a free_func, use that. */
    if (it) {
        const ASN1_PRIMITIVE_FUNCS *pf = it->funcs;

        if (embed) {
            if (pf && pf->prim_clear) {
                pf->prim_clear(pval, it);
                return;
            }
        } else if (pf && pf->prim_free) {
            pf->prim_free(pval, it);
            return;
        }
    }

    /* Special case: if 'it' is NULL, free contents of ASN1_TYPE */
    if (!it) {
        ASN1_TYPE *typ = (ASN1_TYPE *)*pval;

        utype = typ->type;
        pval = &typ->value.asn1_value;
        if (*pval == NULL)
            return;
    } else if (it->itype == ASN1_ITYPE_MSTRING) {
        utype = -1;
        if (*pval == NULL)
            return;
    } else {
        utype = it->utype;
        if ((utype != V_ASN1_BOOLEAN) && *pval == NULL)
            return;
    }

    switch (utype) {
    case V_ASN1_OBJECT:
        ASN1_OBJECT_free((ASN1_OBJECT *)*pval);
        break;

    case V_ASN1_BOOLEAN:
        if (it)
            *(ASN1_BOOLEAN *)pval = it->size;
        else
            *(ASN1_BOOLEAN *)pval = -1;
        return;

    case V_ASN1_NULL:
        break;

    case V_ASN1_ANY:
        asn1_primitive_free(pval, NULL, 0);
        OPENSSL_free(*pval);
        break;

    default:
        asn1_string_embed_free((ASN1_STRING *)*pval, embed);
        break;
    }
    *pval = NULL;
}