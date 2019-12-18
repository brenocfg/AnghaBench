#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_10__ {long long QuadPart; } ;
struct TYPE_9__ {TYPE_1__* FirstSection; } ;
struct TYPE_8__ {struct TYPE_8__* Next; scalar_t__ Data; scalar_t__ Name; } ;
struct TYPE_7__ {struct TYPE_7__* Next; TYPE_2__* FirstKey; scalar_t__ Name; } ;
typedef  TYPE_1__* PINICACHESECTION ;
typedef  TYPE_2__* PINICACHEKEY ;
typedef  TYPE_3__* PINICACHE ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int NTSTATUS ;
typedef  TYPE_4__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int NtWriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int STATUS_INSUFFICIENT_RESOURCES ; 
 int STATUS_SUCCESS ; 
 int sprintf (int /*<<< orphan*/ *,char*,...) ; 
 int wcslen (scalar_t__) ; 

NTSTATUS
IniCacheSaveByHandle(
    PINICACHE Cache,
    HANDLE FileHandle)
{
    NTSTATUS Status;
    PINICACHESECTION Section;
    PINICACHEKEY Key;
    ULONG BufferSize;
    PCHAR Buffer;
    PCHAR Ptr;
    ULONG Len;
    IO_STATUS_BLOCK IoStatusBlock;
    LARGE_INTEGER Offset;

    /* Calculate required buffer size */
    BufferSize = 0;
    Section = Cache->FirstSection;
    while (Section != NULL)
    {
        BufferSize += (Section->Name ? wcslen(Section->Name) : 0)
                       + 4; /* "[]\r\n" */

        Key = Section->FirstKey;
        while (Key != NULL)
        {
            BufferSize += wcslen(Key->Name)
                          + (Key->Data ? wcslen(Key->Data) : 0)
                          + 3; /* "=\r\n" */
            Key = Key->Next;
        }

        Section = Section->Next;
        if (Section != NULL)
            BufferSize += 2; /* Extra "\r\n" at end of each section */
    }

    DPRINT("BufferSize: %lu\n", BufferSize);

    /* Allocate file buffer with NULL-terminator */
    Buffer = (CHAR*)RtlAllocateHeap(ProcessHeap,
                                    HEAP_ZERO_MEMORY,
                                    BufferSize + 1);
    if (Buffer == NULL)
    {
        DPRINT1("RtlAllocateHeap() failed\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Fill file buffer */
    Ptr = Buffer;
    Section = Cache->FirstSection;
    while (Section != NULL)
    {
        Len = sprintf(Ptr, "[%S]\r\n", Section->Name);
        Ptr += Len;

        Key = Section->FirstKey;
        while (Key != NULL)
        {
            Len = sprintf(Ptr, "%S=%S\r\n", Key->Name, Key->Data);
            Ptr += Len;
            Key = Key->Next;
        }

        Section = Section->Next;
        if (Section != NULL)
        {
            Len = sprintf(Ptr, "\r\n");
            Ptr += Len;
        }
    }

    /* Write to the INI file */
    Offset.QuadPart = 0LL;
    Status = NtWriteFile(FileHandle,
                         NULL,
                         NULL,
                         NULL,
                         &IoStatusBlock,
                         Buffer,
                         BufferSize,
                         &Offset,
                         NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtWriteFile() failed (Status %lx)\n", Status);
        RtlFreeHeap(ProcessHeap, 0, Buffer);
        return Status;
    }

    RtlFreeHeap(ProcessHeap, 0, Buffer);
    return STATUS_SUCCESS;
}