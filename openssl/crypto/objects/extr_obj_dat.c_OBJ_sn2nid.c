#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nid; } ;
struct TYPE_8__ {TYPE_1__* obj; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {char const* sn; int nid; } ;
typedef  TYPE_1__ ASN1_OBJECT ;
typedef  TYPE_2__ ADDED_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  ADDED_SNAME ; 
 int NID_undef ; 
 int /*<<< orphan*/  NUM_SN ; 
 unsigned int* OBJ_bsearch_sn (TYPE_1__ const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * added ; 
 TYPE_2__* lh_ADDED_OBJ_retrieve (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__* nid_objs ; 
 int /*<<< orphan*/  sn_objs ; 

int OBJ_sn2nid(const char *s)
{
    ASN1_OBJECT o;
    const ASN1_OBJECT *oo = &o;
    ADDED_OBJ ad, *adp;
    const unsigned int *op;

    /* Make sure we've loaded config before checking for any "added" objects */
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);

    o.sn = s;
    if (added != NULL) {
        ad.type = ADDED_SNAME;
        ad.obj = &o;
        adp = lh_ADDED_OBJ_retrieve(added, &ad);
        if (adp != NULL)
            return adp->obj->nid;
    }
    op = OBJ_bsearch_sn(&oo, sn_objs, NUM_SN);
    if (op == NULL)
        return NID_undef;
    return nid_objs[*op].nid;
}