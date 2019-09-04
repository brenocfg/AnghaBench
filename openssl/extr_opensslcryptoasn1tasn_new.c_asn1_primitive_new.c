#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ itype; int utype; int /*<<< orphan*/  size; TYPE_4__* funcs; } ;
struct TYPE_15__ {int (* prim_new ) (int /*<<< orphan*/ **,TYPE_5__ const*) ;int /*<<< orphan*/  (* prim_clear ) (int /*<<< orphan*/ **,TYPE_5__ const*) ;} ;
struct TYPE_14__ {int type; int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_13__ {int type; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_2__ ASN1_TYPE ;
typedef  TYPE_3__ ASN1_STRING ;
typedef  TYPE_4__ ASN1_PRIMITIVE_FUNCS ;
typedef  TYPE_5__ ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_PRIMITIVE_NEW ; 
 scalar_t__ ASN1_ITYPE_MSTRING ; 
 int /*<<< orphan*/  ASN1_STRING_FLAG_EMBED ; 
 int /*<<< orphan*/  ASN1_STRING_FLAG_MSTRING ; 
 TYPE_3__* ASN1_STRING_type_new (int) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_undef ; 
 scalar_t__ OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 TYPE_2__* OPENSSL_malloc (int) ; 
#define  V_ASN1_ANY 131 
#define  V_ASN1_BOOLEAN 130 
#define  V_ASN1_NULL 129 
#define  V_ASN1_OBJECT 128 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_5__ const*) ; 
 int stub2 (int /*<<< orphan*/ **,TYPE_5__ const*) ; 

__attribute__((used)) static int asn1_primitive_new(ASN1_VALUE **pval, const ASN1_ITEM *it,
                              int embed)
{
    ASN1_TYPE *typ;
    ASN1_STRING *str;
    int utype;

    if (!it)
        return 0;

    if (it->funcs) {
        const ASN1_PRIMITIVE_FUNCS *pf = it->funcs;
        if (embed) {
            if (pf->prim_clear) {
                pf->prim_clear(pval, it);
                return 1;
            }
        } else if (pf->prim_new) {
            return pf->prim_new(pval, it);
        }
    }

    if (it->itype == ASN1_ITYPE_MSTRING)
        utype = -1;
    else
        utype = it->utype;
    switch (utype) {
    case V_ASN1_OBJECT:
        *pval = (ASN1_VALUE *)OBJ_nid2obj(NID_undef);
        return 1;

    case V_ASN1_BOOLEAN:
        *(ASN1_BOOLEAN *)pval = it->size;
        return 1;

    case V_ASN1_NULL:
        *pval = (ASN1_VALUE *)1;
        return 1;

    case V_ASN1_ANY:
        if ((typ = OPENSSL_malloc(sizeof(*typ))) == NULL) {
            ASN1err(ASN1_F_ASN1_PRIMITIVE_NEW, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        typ->value.ptr = NULL;
        typ->type = -1;
        *pval = (ASN1_VALUE *)typ;
        break;

    default:
        if (embed) {
            str = *(ASN1_STRING **)pval;
            memset(str, 0, sizeof(*str));
            str->type = utype;
            str->flags = ASN1_STRING_FLAG_EMBED;
        } else {
            str = ASN1_STRING_type_new(utype);
            *pval = (ASN1_VALUE *)str;
        }
        if (it->itype == ASN1_ITYPE_MSTRING && str)
            str->flags |= ASN1_STRING_FLAG_MSTRING;
        break;
    }
    if (*pval)
        return 1;
    return 0;
}