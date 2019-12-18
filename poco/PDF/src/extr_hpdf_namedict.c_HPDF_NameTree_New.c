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
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_NameTree ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_NAMETREE ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 

HPDF_NameTree
HPDF_NameTree_New  (HPDF_MMgr  mmgr,
                    HPDF_Xref  xref)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_NameTree ntree;
    HPDF_Array items;

    HPDF_PTRACE((" HPDF_NameTree_New\n"));

    ntree = HPDF_Dict_New (mmgr);
    if (!ntree)
        return NULL;

    if (HPDF_Xref_Add (xref, ntree) != HPDF_OK)
        return NULL;

    ntree->header.obj_class |= HPDF_OSUBCLASS_NAMETREE;

    items = HPDF_Array_New (mmgr);
    if (!ntree)
        return NULL;

    ret += HPDF_Dict_Add (ntree, "Names", items);
    if (ret != HPDF_OK)
        return NULL;

    return ntree;
}