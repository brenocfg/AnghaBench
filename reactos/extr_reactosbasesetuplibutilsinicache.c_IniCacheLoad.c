#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/ * PINICACHE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int FILE_GENERIC_READ ; 
 int FILE_NON_DIRECTORY_FILE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int FILE_SYNCHRONOUS_IO_NONALERT ; 
 int /*<<< orphan*/  IniCacheLoadByHandle (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SYNCHRONIZE ; 

NTSTATUS
IniCacheLoad(
    PINICACHE *Cache,
    PWCHAR FileName,
    BOOLEAN String)
{
    NTSTATUS Status;
    UNICODE_STRING Name;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE FileHandle;

    *Cache = NULL;

    /* Open the INI file */
    RtlInitUnicodeString(&Name, FileName);

    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtOpenFile(&FileHandle,
                        FILE_GENERIC_READ | SYNCHRONIZE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ,
                        FILE_SYNCHRONOUS_IO_NONALERT | FILE_NON_DIRECTORY_FILE);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtOpenFile() failed (Status %lx)\n", Status);
        return Status;
    }

    DPRINT("NtOpenFile() successful\n");

    Status = IniCacheLoadByHandle(Cache, FileHandle, String);

    /* Close the INI file */
    NtClose(FileHandle);
    return Status;
}