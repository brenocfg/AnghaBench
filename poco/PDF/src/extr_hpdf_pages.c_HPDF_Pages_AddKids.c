#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* parent; } ;
struct TYPE_11__ {int obj_class; } ;
struct TYPE_12__ {int /*<<< orphan*/  attr; TYPE_1__ header; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Pages ;
typedef  TYPE_3__* HPDF_PageAttr ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  scalar_t__ HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Add (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_2__*,char*,TYPE_2__*) ; 
 scalar_t__ HPDF_Dict_GetItem (TYPE_2__*,char*,int) ; 
 int HPDF_OCLASS_ARRAY ; 
 int HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int HPDF_OSUBCLASS_PAGE ; 
 int /*<<< orphan*/  HPDF_PAGES_MISSING_KIDS_ENTRY ; 
 int /*<<< orphan*/  HPDF_PAGE_CANNOT_SET_PARENT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Pages_AddKids  (HPDF_Pages  parent,
                     HPDF_Dict   kid)
{
    HPDF_Array kids;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Pages_AddKids\n"));

    if (HPDF_Dict_GetItem (kid, "Parent", HPDF_OCLASS_DICT))
        return HPDF_SetError (parent->error, HPDF_PAGE_CANNOT_SET_PARENT, 0);

    if ((ret = HPDF_Dict_Add (kid, "Parent", parent)) != HPDF_OK)
        return ret;

    kids = (HPDF_Array )HPDF_Dict_GetItem (parent, "Kids", HPDF_OCLASS_ARRAY);
    if (!kids)
        return HPDF_SetError (parent->error, HPDF_PAGES_MISSING_KIDS_ENTRY, 0);

    if (kid->header.obj_class == (HPDF_OCLASS_DICT | HPDF_OSUBCLASS_PAGE)) {
        HPDF_PageAttr attr = (HPDF_PageAttr)kid->attr;

        attr->parent = parent;
    }

    return HPDF_Array_Add (kids, kid);
}