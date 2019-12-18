#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_12__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  before_write_fn; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_Pages ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_2__*,char*,char*) ; 
 TYPE_2__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Number_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_PAGES ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Pages_AddKids (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Pages_BeforeWrite ; 

HPDF_Pages
HPDF_Pages_New  (HPDF_MMgr   mmgr,
                 HPDF_Pages  parent,
                 HPDF_Xref   xref)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Pages pages;


    HPDF_PTRACE((" HPDF_Pages_New\n"));

    pages = HPDF_Dict_New (mmgr);
    if (!pages)
        return NULL;

    pages->header.obj_class |= HPDF_OSUBCLASS_PAGES;
    pages->before_write_fn = Pages_BeforeWrite;

    if (HPDF_Xref_Add (xref, pages) != HPDF_OK)
        return NULL;

    /* add requiered elements */
    ret += HPDF_Dict_AddName (pages, "Type", "Pages");
    ret += HPDF_Dict_Add (pages, "Kids", HPDF_Array_New (pages->mmgr));
    ret += HPDF_Dict_Add (pages, "Count", HPDF_Number_New (pages->mmgr, 0));

    if (ret == HPDF_OK && parent)
        ret += HPDF_Pages_AddKids (parent, pages);

    if (ret != HPDF_OK)
        return NULL;

    return pages;
}