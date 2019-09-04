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
struct TYPE_7__ {int LowPart; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
struct TYPE_10__ {TYPE_2__ EndOfFile; } ;
struct TYPE_9__ {unsigned long long QuadPart; } ;
typedef  int /*<<< orphan*/ * PINICACHE ;
typedef  scalar_t__* PCHAR ;
typedef  int NTSTATUS ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_4__ FILE_STANDARD_INFORMATION ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  FileStandardInformation ; 
 int IniCacheLoadFromMemory (int /*<<< orphan*/ **,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int NtQueryInformationFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int NtReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int STATUS_INSUFFICIENT_RESOURCES ; 

NTSTATUS
IniCacheLoadByHandle(
    PINICACHE *Cache,
    HANDLE FileHandle,
    BOOLEAN String)
{
    NTSTATUS Status;
    IO_STATUS_BLOCK IoStatusBlock;
    FILE_STANDARD_INFORMATION FileInfo;
    PCHAR FileBuffer;
    ULONG FileLength;
    LARGE_INTEGER FileOffset;

    *Cache = NULL;

    /* Query file size */
    Status = NtQueryInformationFile(FileHandle,
                                    &IoStatusBlock,
                                    &FileInfo,
                                    sizeof(FILE_STANDARD_INFORMATION),
                                    FileStandardInformation);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtQueryInformationFile() failed (Status %lx)\n", Status);
        return Status;
    }

    FileLength = FileInfo.EndOfFile.u.LowPart;

    DPRINT("File size: %lu\n", FileLength);

    /* Allocate file buffer with NULL-terminator */
    FileBuffer = (CHAR*)RtlAllocateHeap(ProcessHeap,
                                        0,
                                        FileLength + 1);
    if (FileBuffer == NULL)
    {
        DPRINT1("RtlAllocateHeap() failed\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Read file */
    FileOffset.QuadPart = 0ULL;
    Status = NtReadFile(FileHandle,
                        NULL,
                        NULL,
                        NULL,
                        &IoStatusBlock,
                        FileBuffer,
                        FileLength,
                        &FileOffset,
                        NULL);

    /* Append NULL-terminator */
    FileBuffer[FileLength] = 0;

    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtReadFile() failed (Status %lx)\n", Status);
        goto Quit;
    }

    Status = IniCacheLoadFromMemory(Cache, FileBuffer, FileLength, String);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("IniCacheLoadFromMemory() failed (Status %lx)\n", Status);
    }

Quit:
    /* Free the file buffer, and return */
    RtlFreeHeap(ProcessHeap, 0, FileBuffer);
    return Status;
}