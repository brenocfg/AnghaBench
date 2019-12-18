#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ count; } ;
struct TYPE_8__ {int /*<<< orphan*/  mmgr; struct TYPE_8__* prev; scalar_t__ trailer; TYPE_6__* entries; scalar_t__ obj; } ;
typedef  TYPE_1__* HPDF_XrefEntry ;
typedef  TYPE_1__* HPDF_Xref ;
typedef  scalar_t__ HPDF_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Dict_Free (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_List_Free (TYPE_6__*) ; 
 int /*<<< orphan*/  HPDF_Obj_ForceFree (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 TYPE_1__* HPDF_Xref_GetEntry (TYPE_1__*,scalar_t__) ; 

void
HPDF_Xref_Free  (HPDF_Xref  xref)
{
    HPDF_UINT i;
    HPDF_XrefEntry entry;
    HPDF_Xref tmp_xref;

    HPDF_PTRACE((" HPDF_Xref_Free\n"));

    /* delete xref entries. where prev element is not NULL,
     * delete all xref entries recursively.
     */
    while (xref) {
        /* delete all objects belong to the xref. */

        if (xref->entries) {
            for (i = 0; i < xref->entries->count; i++) {
                entry = HPDF_Xref_GetEntry (xref, i);
                if (entry->obj)
                    HPDF_Obj_ForceFree (xref->mmgr, entry->obj);
                HPDF_FreeMem (xref->mmgr, entry);
            }

            HPDF_List_Free(xref->entries);
        }

        if (xref->trailer)
            HPDF_Dict_Free (xref->trailer);

        tmp_xref = xref->prev;
        HPDF_FreeMem (xref->mmgr, xref);
        xref = tmp_xref;
    }
}