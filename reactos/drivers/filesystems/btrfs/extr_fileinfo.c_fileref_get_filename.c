#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct TYPE_13__* parent; TYPE_4__* dc; TYPE_2__* fcb; } ;
typedef  TYPE_5__ file_ref ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
typedef  int ULONG ;
struct TYPE_14__ {int MaximumLength; char* Buffer; int Length; } ;
struct TYPE_11__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_12__ {TYPE_3__ name; } ;
struct TYPE_10__ {scalar_t__ ads; TYPE_1__* Vcb; } ;
struct TYPE_9__ {TYPE_5__* root_fileref; } ;
typedef  TYPE_6__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlMoveMemory (char*,char*,int) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  min (int,int) ; 

NTSTATUS fileref_get_filename(file_ref* fileref, PUNICODE_STRING fn, USHORT* name_offset, ULONG* preqlen) {
    file_ref* fr;
    NTSTATUS Status;
    ULONG reqlen = 0;
    USHORT offset;
    bool overflow = false;

    // FIXME - we need a lock on filerefs' filepart

    if (fileref == fileref->fcb->Vcb->root_fileref) {
        if (fn->MaximumLength >= sizeof(WCHAR)) {
            fn->Buffer[0] = '\\';
            fn->Length = sizeof(WCHAR);

            if (name_offset)
                *name_offset = 0;

            return STATUS_SUCCESS;
        } else {
            if (preqlen)
                *preqlen = sizeof(WCHAR);
            fn->Length = 0;

            return STATUS_BUFFER_OVERFLOW;
        }
    }

    fr = fileref;
    offset = 0;

    while (fr->parent) {
        USHORT movelen;

        if (!fr->dc)
            return STATUS_INTERNAL_ERROR;

        if (!overflow) {
            if (fr->dc->name.Length + sizeof(WCHAR) + fn->Length > fn->MaximumLength)
                overflow = true;
        }

        if (overflow)
            movelen = fn->MaximumLength - fr->dc->name.Length - sizeof(WCHAR);
        else
            movelen = fn->Length;

        if ((!overflow || fn->MaximumLength > fr->dc->name.Length + sizeof(WCHAR)) && movelen > 0) {
            RtlMoveMemory(&fn->Buffer[(fr->dc->name.Length / sizeof(WCHAR)) + 1], fn->Buffer, movelen);
            offset += fr->dc->name.Length + sizeof(WCHAR);
        }

        if (fn->MaximumLength >= sizeof(WCHAR)) {
            fn->Buffer[0] = fr->fcb->ads ? ':' : '\\';
            fn->Length += sizeof(WCHAR);

            if (fn->MaximumLength > sizeof(WCHAR)) {
                RtlCopyMemory(&fn->Buffer[1], fr->dc->name.Buffer, min(fr->dc->name.Length, fn->MaximumLength - sizeof(WCHAR)));
                fn->Length += fr->dc->name.Length;
            }

            if (fn->Length > fn->MaximumLength) {
                fn->Length = fn->MaximumLength;
                overflow = true;
            }
        }

        reqlen += sizeof(WCHAR) + fr->dc->name.Length;

        fr = fr->parent;
    }

    offset += sizeof(WCHAR);

    if (overflow) {
        if (preqlen)
            *preqlen = reqlen;
        Status = STATUS_BUFFER_OVERFLOW;
    } else {
        if (name_offset)
            *name_offset = offset;

        Status = STATUS_SUCCESS;
    }

    return Status;
}