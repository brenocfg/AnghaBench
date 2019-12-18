#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_5__ {TYPE_3__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Obj_Header ;
typedef  int /*<<< orphan*/  HPDF_Null_Rec ;
typedef  TYPE_1__* HPDF_Null ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;

/* Variables and functions */
 TYPE_1__* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_OCLASS_NULL ; 

HPDF_Null
HPDF_Null_New  (HPDF_MMgr  mmgr)
{
    HPDF_Null obj = HPDF_GetMem (mmgr, sizeof(HPDF_Null_Rec));

    if (obj) {
        HPDF_MemSet (&obj->header, 0, sizeof(HPDF_Obj_Header));
        obj->header.obj_class = HPDF_OCLASS_NULL;
    }

    return obj;
}