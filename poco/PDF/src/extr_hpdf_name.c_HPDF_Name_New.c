#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_12__ {int /*<<< orphan*/  error; } ;
struct TYPE_11__ {int /*<<< orphan*/  error; TYPE_6__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Obj_Header ;
typedef  int /*<<< orphan*/  HPDF_Name_Rec ;
typedef  TYPE_1__* HPDF_Name ;
typedef  TYPE_2__* HPDF_MMgr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* HPDF_GetMem (TYPE_2__*,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_NAME_INVALID_VALUE ; 
 scalar_t__ HPDF_Name_SetValue (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  HPDF_OCLASS_NAME ; 

HPDF_Name
HPDF_Name_New  (HPDF_MMgr        mmgr,
                const char  *value)
{
    HPDF_Name obj;

    obj  = HPDF_GetMem (mmgr, sizeof(HPDF_Name_Rec));

    if (obj) {
        HPDF_MemSet (&obj->header, 0, sizeof(HPDF_Obj_Header));
        obj->header.obj_class = HPDF_OCLASS_NAME;
        obj->error = mmgr->error;
        if (HPDF_Name_SetValue (obj, value) == HPDF_NAME_INVALID_VALUE) {
            HPDF_FreeMem (mmgr, obj);
            return NULL;
        }
    }

    return obj;
}