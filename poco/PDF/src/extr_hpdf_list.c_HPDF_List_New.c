#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * obj; scalar_t__ count; scalar_t__ items_per_block; scalar_t__ block_siz; int /*<<< orphan*/  error; TYPE_1__* mmgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_List_Rec ;
typedef  TYPE_2__* HPDF_List ;

/* Variables and functions */
 scalar_t__ HPDF_DEF_ITEMS_PER_BLOCK ; 
 scalar_t__ HPDF_GetMem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_List
HPDF_List_New  (HPDF_MMgr  mmgr,
                HPDF_UINT  items_per_block)
{
    HPDF_List list;

    HPDF_PTRACE((" HPDF_List_New\n"));

    if (mmgr == NULL)
        return NULL;

    list = (HPDF_List)HPDF_GetMem (mmgr, sizeof(HPDF_List_Rec));
    if (list) {
        list->mmgr = mmgr;
        list->error = mmgr->error;
        list->block_siz = 0;
        list->items_per_block =
            (items_per_block <= 0 ? HPDF_DEF_ITEMS_PER_BLOCK : items_per_block);
        list->count = 0;
        list->obj = NULL;
    }

    return list;
}