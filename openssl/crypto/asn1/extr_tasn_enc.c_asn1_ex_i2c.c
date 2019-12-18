#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ itype; scalar_t__ utype; int /*<<< orphan*/  size; TYPE_4__* funcs; } ;
struct TYPE_13__ {unsigned char* data; int length; } ;
struct TYPE_12__ {int (* prim_i2c ) (int /*<<< orphan*/  const**,unsigned char*,int*,TYPE_6__ const*) ;} ;
struct TYPE_11__ {int type; int flags; unsigned char* data; int length; } ;
struct TYPE_9__ {int /*<<< orphan*/  asn1_value; } ;
struct TYPE_10__ {int type; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_2__ ASN1_TYPE ;
typedef  TYPE_3__ ASN1_STRING ;
typedef  TYPE_4__ ASN1_PRIMITIVE_FUNCS ;
typedef  TYPE_5__ ASN1_OBJECT ;
typedef  TYPE_6__ ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int ASN1_BOOLEAN ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 scalar_t__ ASN1_ITYPE_MSTRING ; 
 scalar_t__ ASN1_ITYPE_PRIMITIVE ; 
 int ASN1_STRING_FLAG_NDEF ; 
 int /*<<< orphan*/  ASN1_TFLG_NDEF ; 
 scalar_t__ V_ASN1_ANY ; 
#define  V_ASN1_BIT_STRING 149 
#define  V_ASN1_BMPSTRING 148 
#define  V_ASN1_BOOLEAN 147 
#define  V_ASN1_ENUMERATED 146 
#define  V_ASN1_GENERALIZEDTIME 145 
#define  V_ASN1_GENERALSTRING 144 
#define  V_ASN1_GRAPHICSTRING 143 
#define  V_ASN1_IA5STRING 142 
#define  V_ASN1_INTEGER 141 
#define  V_ASN1_NULL 140 
#define  V_ASN1_NUMERICSTRING 139 
#define  V_ASN1_OBJECT 138 
#define  V_ASN1_OCTET_STRING 137 
#define  V_ASN1_PRINTABLESTRING 136 
#define  V_ASN1_SEQUENCE 135 
#define  V_ASN1_SET 134 
#define  V_ASN1_T61STRING 133 
#define  V_ASN1_UNIVERSALSTRING 132 
#define  V_ASN1_UTCTIME 131 
#define  V_ASN1_UTF8STRING 130 
#define  V_ASN1_VIDEOTEXSTRING 129 
#define  V_ASN1_VISIBLESTRING 128 
 int i2c_ASN1_BIT_STRING (int /*<<< orphan*/ *,unsigned char**) ; 
 int i2c_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int stub1 (int /*<<< orphan*/  const**,unsigned char*,int*,TYPE_6__ const*) ; 

__attribute__((used)) static int asn1_ex_i2c(const ASN1_VALUE **pval, unsigned char *cout, int *putype,
                       const ASN1_ITEM *it)
{
    ASN1_BOOLEAN *tbool = NULL;
    ASN1_STRING *strtmp;
    ASN1_OBJECT *otmp;
    int utype;
    const unsigned char *cont;
    unsigned char c;
    int len;
    const ASN1_PRIMITIVE_FUNCS *pf;
    pf = it->funcs;
    if (pf && pf->prim_i2c)
        return pf->prim_i2c(pval, cout, putype, it);

    /* Should type be omitted? */
    if ((it->itype != ASN1_ITYPE_PRIMITIVE)
        || (it->utype != V_ASN1_BOOLEAN)) {
        if (*pval == NULL)
            return -1;
    }

    if (it->itype == ASN1_ITYPE_MSTRING) {
        /* If MSTRING type set the underlying type */
        strtmp = (ASN1_STRING *)*pval;
        utype = strtmp->type;
        *putype = utype;
    } else if (it->utype == V_ASN1_ANY) {
        /* If ANY set type and pointer to value */
        ASN1_TYPE *typ;
        typ = (ASN1_TYPE *)*pval;
        utype = typ->type;
        *putype = utype;
        pval = (const ASN1_VALUE **)&typ->value.asn1_value; /* actually is const */
    } else
        utype = *putype;

    switch (utype) {
    case V_ASN1_OBJECT:
        otmp = (ASN1_OBJECT *)*pval;
        cont = otmp->data;
        len = otmp->length;
        if (cont == NULL || len == 0)
            return -1;
        break;

    case V_ASN1_NULL:
        cont = NULL;
        len = 0;
        break;

    case V_ASN1_BOOLEAN:
        tbool = (ASN1_BOOLEAN *)pval;
        if (*tbool == -1)
            return -1;
        if (it->utype != V_ASN1_ANY) {
            /*
             * Default handling if value == size field then omit
             */
            if (*tbool && (it->size > 0))
                return -1;
            if (!*tbool && !it->size)
                return -1;
        }
        c = (unsigned char)*tbool;
        cont = &c;
        len = 1;
        break;

    case V_ASN1_BIT_STRING:
        return i2c_ASN1_BIT_STRING((ASN1_BIT_STRING *)*pval,
                                   cout ? &cout : NULL);

    case V_ASN1_INTEGER:
    case V_ASN1_ENUMERATED:
        /*
         * These are all have the same content format as ASN1_INTEGER
         */
        return i2c_ASN1_INTEGER((ASN1_INTEGER *)*pval, cout ? &cout : NULL);

    case V_ASN1_OCTET_STRING:
    case V_ASN1_NUMERICSTRING:
    case V_ASN1_PRINTABLESTRING:
    case V_ASN1_T61STRING:
    case V_ASN1_VIDEOTEXSTRING:
    case V_ASN1_IA5STRING:
    case V_ASN1_UTCTIME:
    case V_ASN1_GENERALIZEDTIME:
    case V_ASN1_GRAPHICSTRING:
    case V_ASN1_VISIBLESTRING:
    case V_ASN1_GENERALSTRING:
    case V_ASN1_UNIVERSALSTRING:
    case V_ASN1_BMPSTRING:
    case V_ASN1_UTF8STRING:
    case V_ASN1_SEQUENCE:
    case V_ASN1_SET:
    default:
        /* All based on ASN1_STRING and handled the same */
        strtmp = (ASN1_STRING *)*pval;
        /* Special handling for NDEF */
        if ((it->size == ASN1_TFLG_NDEF)
            && (strtmp->flags & ASN1_STRING_FLAG_NDEF)) {
            if (cout) {
                strtmp->data = cout;
                strtmp->length = 0;
            }
            /* Special return code */
            return -2;
        }
        cont = strtmp->data;
        len = strtmp->length;

        break;

    }
    if (cout && len)
        memcpy(cout, cont, len);
    return len;
}