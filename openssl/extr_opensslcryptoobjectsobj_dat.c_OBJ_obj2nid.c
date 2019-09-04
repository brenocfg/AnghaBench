#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nid; } ;
struct TYPE_9__ {TYPE_1__* obj; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {scalar_t__ nid; scalar_t__ length; } ;
typedef  TYPE_1__ ASN1_OBJECT ;
typedef  TYPE_2__ ADDED_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  ADDED_DATA ; 
 int NID_undef ; 
 int /*<<< orphan*/  NUM_OBJ ; 
 unsigned int* OBJ_bsearch_obj (TYPE_1__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * added ; 
 TYPE_2__* lh_ADDED_OBJ_retrieve (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__* nid_objs ; 
 int /*<<< orphan*/  obj_objs ; 

int OBJ_obj2nid(const ASN1_OBJECT *a)
{
    const unsigned int *op;
    ADDED_OBJ ad, *adp;

    if (a == NULL)
        return NID_undef;
    if (a->nid != 0)
        return a->nid;

    if (a->length == 0)
        return NID_undef;

    if (added != NULL) {
        ad.type = ADDED_DATA;
        ad.obj = (ASN1_OBJECT *)a; /* XXX: ugly but harmless */
        adp = lh_ADDED_OBJ_retrieve(added, &ad);
        if (adp != NULL)
            return adp->obj->nid;
    }
    op = OBJ_bsearch_obj(&a, obj_objs, NUM_OBJ);
    if (op == NULL)
        return NID_undef;
    return nid_objs[*op].nid;
}