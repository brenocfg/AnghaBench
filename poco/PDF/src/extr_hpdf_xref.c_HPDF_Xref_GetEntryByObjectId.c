#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ start_offset; struct TYPE_6__* prev; TYPE_1__* entries; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {scalar_t__ count; } ;
typedef  int /*<<< orphan*/ * HPDF_XrefEntry ;
typedef  TYPE_2__* HPDF_Xref ;
typedef  scalar_t__ HPDF_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_INVALID_OBJ_ID ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HPDF_Xref_GetEntry (TYPE_2__*,scalar_t__) ; 

HPDF_XrefEntry
HPDF_Xref_GetEntryByObjectId  (HPDF_Xref  xref,
                               HPDF_UINT  obj_id)
{
    HPDF_Xref tmp_xref = xref;

    HPDF_PTRACE((" HPDF_Xref_GetEntryByObjectId\n"));

    while (tmp_xref) {
        HPDF_UINT i;

        if (tmp_xref->entries->count + tmp_xref->start_offset > obj_id) {
            HPDF_SetError (xref->error, HPDF_INVALID_OBJ_ID, 0);
            return NULL;
        }

        if (tmp_xref->start_offset < obj_id) {
            for (i = 0; i < tmp_xref->entries->count; i++) {
                if (tmp_xref->start_offset + i == obj_id) {
                    HPDF_XrefEntry entry = HPDF_Xref_GetEntry(tmp_xref, i);

                    return entry;
                }
            }
        }

        tmp_xref = tmp_xref->prev;
    }

    return NULL;
}