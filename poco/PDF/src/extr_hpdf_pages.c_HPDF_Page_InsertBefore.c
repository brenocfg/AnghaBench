#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ attr; int /*<<< orphan*/  error; } ;
struct TYPE_10__ {TYPE_2__* parent; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_PageAttr ;
typedef  TYPE_2__* HPDF_Page ;
typedef  scalar_t__ HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Insert (scalar_t__,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_2__*,char*,TYPE_2__*) ; 
 scalar_t__ HPDF_Dict_GetItem (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_INVALID_PARAMETER ; 
 int /*<<< orphan*/  HPDF_OCLASS_ARRAY ; 
 int /*<<< orphan*/  HPDF_OCLASS_DICT ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PAGES_MISSING_KIDS_ENTRY ; 
 int /*<<< orphan*/  HPDF_PAGE_CANNOT_SET_PARENT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Page_InsertBefore  (HPDF_Page   page,
                         HPDF_Page   target)
{
    HPDF_Page parent;
    HPDF_Array kids;
    HPDF_STATUS ret;
    HPDF_PageAttr attr;

    HPDF_PTRACE((" HPDF_Page_InsertBefore\n"));

    if (!target)
        return HPDF_INVALID_PARAMETER;

    attr = (HPDF_PageAttr )target->attr;
    parent = attr->parent;

    if (!parent)
        return HPDF_PAGE_CANNOT_SET_PARENT;

    if (HPDF_Dict_GetItem (page, "Parent", HPDF_OCLASS_DICT))
        return HPDF_SetError (parent->error, HPDF_PAGE_CANNOT_SET_PARENT, 0);

    if ((ret = HPDF_Dict_Add (page, "Parent", parent)) != HPDF_OK)
        return ret;

    kids = (HPDF_Array )HPDF_Dict_GetItem (parent, "Kids", HPDF_OCLASS_ARRAY);
    if (!kids)
        return HPDF_SetError (parent->error, HPDF_PAGES_MISSING_KIDS_ENTRY, 0);

    attr = (HPDF_PageAttr)page->attr;
    attr->parent = parent;

    return HPDF_Array_Insert (kids, target, page);
}