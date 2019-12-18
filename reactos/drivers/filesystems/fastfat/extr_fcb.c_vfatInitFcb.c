#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  VFATFCB ;
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_19__ {scalar_t__ Length; scalar_t__ MaximumLength; int /*<<< orphan*/ * Buffer; } ;
struct TYPE_18__ {scalar_t__ Length; scalar_t__ MaximumLength; scalar_t__ Buffer; } ;
struct TYPE_17__ {scalar_t__ Buffer; scalar_t__ MaximumLength; scalar_t__ Length; } ;
struct TYPE_16__ {scalar_t__ Length; } ;
struct TYPE_14__ {int MaximumLength; int /*<<< orphan*/  Buffer; scalar_t__ Length; } ;
struct TYPE_13__ {int NodeByteSize; int /*<<< orphan*/  NodeTypeCode; } ;
struct TYPE_15__ {scalar_t__ OpenHandleCount; int /*<<< orphan*/  FCBShareAccess; TYPE_7__ LongNameU; TYPE_6__ DirNameU; TYPE_5__ PathNameU; TYPE_2__ ShortNameU; int /*<<< orphan*/  ShortNameBuffer; scalar_t__ PathNameBuffer; TYPE_1__ RFCB; } ;
typedef  int /*<<< orphan*/  SHARE_ACCESS ;
typedef  TYPE_3__* PVFATFCB ;
typedef  TYPE_4__* PUNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_4__*) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAT_FILE_SYSTEM ; 
 int /*<<< orphan*/  KeBugCheckEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODE_TYPE_FCB ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyUnicodeString (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TAG_FCB ; 
 int /*<<< orphan*/  vfatSplitPathName (TYPE_5__*,TYPE_6__*,TYPE_7__*) ; 

__attribute__((used)) static
VOID
vfatInitFcb(
    PVFATFCB Fcb,
    PUNICODE_STRING NameU)
{
    USHORT PathNameBufferLength;

    if (NameU)
        PathNameBufferLength = NameU->Length + sizeof(WCHAR);
    else
        PathNameBufferLength = 0;

    Fcb->PathNameBuffer = ExAllocatePoolWithTag(NonPagedPool, PathNameBufferLength, TAG_FCB);
    if (!Fcb->PathNameBuffer)
    {
        /* FIXME: what to do if no more memory? */
        DPRINT1("Unable to initialize FCB for filename '%wZ'\n", NameU);
        KeBugCheckEx(FAT_FILE_SYSTEM, (ULONG_PTR)Fcb, (ULONG_PTR)NameU, 0, 0);
    }

    Fcb->RFCB.NodeTypeCode = NODE_TYPE_FCB;
    Fcb->RFCB.NodeByteSize = sizeof(VFATFCB);

    Fcb->PathNameU.Length = 0;
    Fcb->PathNameU.Buffer = Fcb->PathNameBuffer;
    Fcb->PathNameU.MaximumLength = PathNameBufferLength;
    Fcb->ShortNameU.Length = 0;
    Fcb->ShortNameU.Buffer = Fcb->ShortNameBuffer;
    Fcb->ShortNameU.MaximumLength = sizeof(Fcb->ShortNameBuffer);
    Fcb->DirNameU.Buffer = Fcb->PathNameU.Buffer;
    if (NameU && NameU->Length)
    {
        RtlCopyUnicodeString(&Fcb->PathNameU, NameU);
        vfatSplitPathName(&Fcb->PathNameU, &Fcb->DirNameU, &Fcb->LongNameU);
    }
    else
    {
        Fcb->DirNameU.Buffer = Fcb->LongNameU.Buffer = NULL;
        Fcb->DirNameU.MaximumLength = Fcb->DirNameU.Length = 0;
        Fcb->LongNameU.MaximumLength = Fcb->LongNameU.Length = 0;
    }
    RtlZeroMemory(&Fcb->FCBShareAccess, sizeof(SHARE_ACCESS));
    Fcb->OpenHandleCount = 0;
}