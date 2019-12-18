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
struct TYPE_6__ {scalar_t__ itype; int utype; int /*<<< orphan*/  size; TYPE_1__* funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* prim_clear ) (int /*<<< orphan*/ **,TYPE_2__ const*) ;} ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_PRIMITIVE_FUNCS ;
typedef  TYPE_2__ ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_BOOLEAN ;

/* Variables and functions */
 scalar_t__ ASN1_ITYPE_MSTRING ; 
 int V_ASN1_BOOLEAN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,TYPE_2__ const*) ; 

__attribute__((used)) static void asn1_primitive_clear(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    int utype;
    if (it && it->funcs) {
        const ASN1_PRIMITIVE_FUNCS *pf = it->funcs;
        if (pf->prim_clear)
            pf->prim_clear(pval, it);
        else
            *pval = NULL;
        return;
    }
    if (!it || (it->itype == ASN1_ITYPE_MSTRING))
        utype = -1;
    else
        utype = it->utype;
    if (utype == V_ASN1_BOOLEAN)
        *(ASN1_BOOLEAN *)pval = it->size;
    else
        *pval = NULL;
}