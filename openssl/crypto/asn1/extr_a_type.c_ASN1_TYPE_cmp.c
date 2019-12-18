#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int boolean; scalar_t__ ptr; int /*<<< orphan*/  object; } ;
struct TYPE_6__ {int type; TYPE_1__ value; } ;
typedef  TYPE_2__ ASN1_TYPE ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int OBJ_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  V_ASN1_BIT_STRING 150 
#define  V_ASN1_BMPSTRING 149 
#define  V_ASN1_BOOLEAN 148 
#define  V_ASN1_ENUMERATED 147 
#define  V_ASN1_GENERALIZEDTIME 146 
#define  V_ASN1_GENERALSTRING 145 
#define  V_ASN1_GRAPHICSTRING 144 
#define  V_ASN1_IA5STRING 143 
#define  V_ASN1_INTEGER 142 
#define  V_ASN1_NULL 141 
#define  V_ASN1_NUMERICSTRING 140 
#define  V_ASN1_OBJECT 139 
#define  V_ASN1_OCTET_STRING 138 
#define  V_ASN1_OTHER 137 
#define  V_ASN1_PRINTABLESTRING 136 
#define  V_ASN1_SEQUENCE 135 
#define  V_ASN1_SET 134 
#define  V_ASN1_T61STRING 133 
#define  V_ASN1_UNIVERSALSTRING 132 
#define  V_ASN1_UTCTIME 131 
#define  V_ASN1_UTF8STRING 130 
#define  V_ASN1_VIDEOTEXSTRING 129 
#define  V_ASN1_VISIBLESTRING 128 

int ASN1_TYPE_cmp(const ASN1_TYPE *a, const ASN1_TYPE *b)
{
    int result = -1;

    if (!a || !b || a->type != b->type)
        return -1;

    switch (a->type) {
    case V_ASN1_OBJECT:
        result = OBJ_cmp(a->value.object, b->value.object);
        break;
    case V_ASN1_BOOLEAN:
        result = a->value.boolean - b->value.boolean;
        break;
    case V_ASN1_NULL:
        result = 0;             /* They do not have content. */
        break;
    case V_ASN1_INTEGER:
    case V_ASN1_ENUMERATED:
    case V_ASN1_BIT_STRING:
    case V_ASN1_OCTET_STRING:
    case V_ASN1_SEQUENCE:
    case V_ASN1_SET:
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
    case V_ASN1_OTHER:
    default:
        result = ASN1_STRING_cmp((ASN1_STRING *)a->value.ptr,
                                 (ASN1_STRING *)b->value.ptr);
        break;
    }

    return result;
}