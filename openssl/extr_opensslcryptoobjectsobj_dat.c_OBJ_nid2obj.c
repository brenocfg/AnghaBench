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
struct TYPE_7__ {int nid; } ;
typedef  TYPE_1__ ASN1_OBJECT ;
typedef  TYPE_2__ ADDED_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  ADDED_NID ; 
 int NID_undef ; 
 int NUM_NID ; 
 int /*<<< orphan*/  OBJ_F_OBJ_NID2OBJ ; 
 int /*<<< orphan*/  OBJ_R_UNKNOWN_NID ; 
 int /*<<< orphan*/  OBJerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * added ; 
 TYPE_2__* lh_ADDED_OBJ_retrieve (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__* nid_objs ; 

ASN1_OBJECT *OBJ_nid2obj(int n)
{
    ADDED_OBJ ad, *adp;
    ASN1_OBJECT ob;

    if ((n >= 0) && (n < NUM_NID)) {
        if ((n != NID_undef) && (nid_objs[n].nid == NID_undef)) {
            OBJerr(OBJ_F_OBJ_NID2OBJ, OBJ_R_UNKNOWN_NID);
            return NULL;
        }
        return (ASN1_OBJECT *)&(nid_objs[n]);
    } else if (added == NULL)
        return NULL;
    else {
        ad.type = ADDED_NID;
        ad.obj = &ob;
        ob.nid = n;
        adp = lh_ADDED_OBJ_retrieve(added, &ad);
        if (adp != NULL)
            return adp->obj;
        else {
            OBJerr(OBJ_F_OBJ_NID2OBJ, OBJ_R_UNKNOWN_NID);
            return NULL;
        }
    }
}