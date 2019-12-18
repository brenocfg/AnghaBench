#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_16__ {int AttributeOffset; int BytesInUse; } ;
struct TYPE_15__ {int Offset; TYPE_1__* CurrAttr; TYPE_1__* FirstAttr; int /*<<< orphan*/ * NonResidentEnd; int /*<<< orphan*/ * NonResidentStart; TYPE_1__* LastAttr; int /*<<< orphan*/  OnlyResident; int /*<<< orphan*/  Vcb; } ;
struct TYPE_14__ {scalar_t__ Type; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PNTFS_ATTR_RECORD ;
typedef  TYPE_3__* PFIND_ATTR_CONTXT ;
typedef  TYPE_4__* PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ AttributeAttributeList ; 
 scalar_t__ AttributeEnd ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 TYPE_1__* InternalGetNextAttribute (TYPE_3__*) ; 
 int /*<<< orphan*/  InternalReadNonResidentAttributes (TYPE_3__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_END_OF_FILE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
FindFirstAttribute(PFIND_ATTR_CONTXT Context,
                   PDEVICE_EXTENSION Vcb,
                   PFILE_RECORD_HEADER FileRecord,
                   BOOLEAN OnlyResident,
                   PNTFS_ATTR_RECORD * Attribute)
{
    NTSTATUS Status;

    DPRINT("FindFistAttribute(%p, %p, %p, %p, %u, %p)\n", Context, Vcb, FileRecord, OnlyResident, Attribute);

    Context->Vcb = Vcb;
    Context->OnlyResident = OnlyResident;
    Context->FirstAttr = (PNTFS_ATTR_RECORD)((ULONG_PTR)FileRecord + FileRecord->AttributeOffset);
    Context->CurrAttr = Context->FirstAttr;
    Context->LastAttr = (PNTFS_ATTR_RECORD)((ULONG_PTR)FileRecord + FileRecord->BytesInUse);
    Context->NonResidentStart = NULL;
    Context->NonResidentEnd = NULL;
    Context->Offset = FileRecord->AttributeOffset;

    if (Context->FirstAttr->Type == AttributeEnd)
    {
        Context->CurrAttr = (PVOID)-1;
        return STATUS_END_OF_FILE;
    }
    else if (Context->FirstAttr->Type == AttributeAttributeList)
    {
        Status = InternalReadNonResidentAttributes(Context);
        if (!NT_SUCCESS(Status))
        {
            return Status;
        }

        *Attribute = InternalGetNextAttribute(Context);
        if (*Attribute == NULL)
        {
            return STATUS_END_OF_FILE;
        }
    }
    else
    {
        *Attribute = Context->CurrAttr;
        Context->Offset = (UCHAR*)Context->CurrAttr - (UCHAR*)FileRecord;
    }

    return STATUS_SUCCESS;
}