#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int count; } ;
struct TYPE_10__ {int obj_id; scalar_t__ gen_no; } ;
struct TYPE_9__ {int start_offset; int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; TYPE_5__* entries; } ;
struct TYPE_8__ {scalar_t__ gen_no; void* obj; scalar_t__ byte_offset; int /*<<< orphan*/  entry_typ; } ;
typedef  int /*<<< orphan*/  HPDF_XrefEntry_Rec ;
typedef  TYPE_1__* HPDF_XrefEntry ;
typedef  TYPE_2__* HPDF_Xref ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_3__ HPDF_Obj_Header ;

/* Variables and functions */
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_INVALID_OBJECT ; 
 int /*<<< orphan*/  HPDF_IN_USE_ENTRY ; 
 int HPDF_LIMIT_MAX_XREF_ELEMENT ; 
 scalar_t__ HPDF_List_Add (TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ HPDF_OK ; 
 int HPDF_OTYPE_DIRECT ; 
 int HPDF_OTYPE_INDIRECT ; 
 int /*<<< orphan*/  HPDF_Obj_ForceFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_XREF_COUNT_ERR ; 

HPDF_STATUS
HPDF_Xref_Add  (HPDF_Xref  xref,
                void       *obj)
{
    HPDF_XrefEntry entry;
    HPDF_Obj_Header *header;

    HPDF_PTRACE((" HPDF_Xref_Add\n"));

    if (!obj) {
        if (HPDF_Error_GetCode (xref->error) == HPDF_OK)
            return HPDF_SetError (xref->error, HPDF_INVALID_OBJECT, 0);
        else
            return HPDF_INVALID_OBJECT;
    }

    header = (HPDF_Obj_Header *)obj;

    if (header->obj_id & HPDF_OTYPE_DIRECT ||
            header->obj_id & HPDF_OTYPE_INDIRECT)
        return HPDF_SetError(xref->error, HPDF_INVALID_OBJECT, 0);

    if (xref->entries->count >= HPDF_LIMIT_MAX_XREF_ELEMENT) {
        HPDF_SetError(xref->error, HPDF_XREF_COUNT_ERR, 0);
        goto Fail;
    }

    /* in the following, we have to dispose the object when an error is
     * occured.
     */

    entry = (HPDF_XrefEntry)HPDF_GetMem (xref->mmgr,
            sizeof(HPDF_XrefEntry_Rec));
    if (entry == NULL)
        goto Fail;

    if (HPDF_List_Add(xref->entries, entry) != HPDF_OK) {
        HPDF_FreeMem (xref->mmgr, entry);
        goto Fail;
    }

    entry->entry_typ = HPDF_IN_USE_ENTRY;
    entry->byte_offset = 0;
    entry->gen_no = 0;
    entry->obj = obj;
    header->obj_id = xref->start_offset + xref->entries->count - 1 +
                    HPDF_OTYPE_INDIRECT;

    header->gen_no = entry->gen_no;

    return HPDF_OK;

Fail:
    HPDF_Obj_ForceFree(xref->mmgr, obj);
    return HPDF_Error_GetCode (xref->error);
}