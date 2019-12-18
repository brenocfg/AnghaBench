#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_8__ {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_2__* HPDF_Dict ;

/* Variables and functions */
 scalar_t__ HPDF_Dict_AddName (TYPE_2__*,char*,char*) ; 
 TYPE_2__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_EXT_GSTATE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 

HPDF_Dict
HPDF_ExtGState_New  (HPDF_MMgr   mmgr, 
                     HPDF_Xref   xref)
{
    HPDF_Dict obj = HPDF_Dict_New (mmgr);

    HPDF_PTRACE ((" HPDF_ExtGState_New\n"));

    if (!obj)
        return NULL;

    if (HPDF_Xref_Add (xref, obj) != HPDF_OK)
        return NULL;

    if (HPDF_Dict_AddName (obj, "Type", "ExtGState") != HPDF_OK)
        return NULL;

    obj->header.obj_class |= HPDF_OSUBCLASS_EXT_GSTATE;

    return obj;
}