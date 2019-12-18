#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_19__ {int /*<<< orphan*/  mmgr; TYPE_2__* attr; int /*<<< orphan*/  before_write_fn; int /*<<< orphan*/  free_fn; TYPE_1__ header; } ;
struct TYPE_18__ {TYPE_12__* contents; int /*<<< orphan*/  xref; int /*<<< orphan*/  stream; int /*<<< orphan*/  gstate; void* text_pos; void* cur_pos; int /*<<< orphan*/  gmode; } ;
struct TYPE_16__ {int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_PageAttr_Rec ;
typedef  TYPE_2__* HPDF_PageAttr ;
typedef  TYPE_3__* HPDF_Page ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_INT16 ;

/* Variables and functions */
 scalar_t__ AddResource (TYPE_3__*) ; 
 TYPE_12__* HPDF_Box_Array_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_DEF_PAGE_HEIGHT ; 
 scalar_t__ HPDF_DEF_PAGE_WIDTH ; 
 TYPE_12__* HPDF_DictStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_3__*,char*,TYPE_12__*) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  HPDF_Dict_Free (TYPE_3__*) ; 
 TYPE_3__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_GMODE_PAGE_DESCRIPTION ; 
 int /*<<< orphan*/  HPDF_GState_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_PAGE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_ToBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* HPDF_ToPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  Page_BeforeWrite ; 
 int /*<<< orphan*/  Page_OnFree ; 

HPDF_Page
HPDF_Page_New  (HPDF_MMgr   mmgr,
                HPDF_Xref   xref)
{
    HPDF_STATUS ret;
    HPDF_PageAttr attr;
    HPDF_Page page;

    HPDF_PTRACE((" HPDF_Page_New\n"));

    page = HPDF_Dict_New (mmgr);
    if (!page)
        return NULL;

    page->header.obj_class |= HPDF_OSUBCLASS_PAGE;
    page->free_fn = Page_OnFree;
    page->before_write_fn = Page_BeforeWrite;

    attr = HPDF_GetMem (page->mmgr, sizeof(HPDF_PageAttr_Rec));
    if (!attr) {
        HPDF_Dict_Free (page);
        return NULL;
    }

    page->attr = attr;
    HPDF_MemSet (attr, 0, sizeof(HPDF_PageAttr_Rec));
    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;
    attr->cur_pos = HPDF_ToPoint (0, 0);
    attr->text_pos = HPDF_ToPoint (0, 0);

    ret = HPDF_Xref_Add (xref, page);
    if (ret != HPDF_OK)
        return NULL;

    attr->gstate = HPDF_GState_New (page->mmgr, NULL);
    attr->contents = HPDF_DictStream_New (page->mmgr, xref);

    if (!attr->gstate || !attr->contents)
        return NULL;

    attr->stream = attr->contents->stream;
    attr->xref = xref;

    /* add requiered elements */
    ret += HPDF_Dict_AddName (page, "Type", "Page");
    ret += HPDF_Dict_Add (page, "MediaBox", HPDF_Box_Array_New (page->mmgr,
                HPDF_ToBox (0, 0, (HPDF_INT16)(HPDF_DEF_PAGE_WIDTH), (HPDF_INT16)(HPDF_DEF_PAGE_HEIGHT))));
    ret += HPDF_Dict_Add (page, "Contents", attr->contents);

    ret += AddResource (page);

    if (ret != HPDF_OK)
        return NULL;

    return page;
}