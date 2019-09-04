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
typedef  int /*<<< orphan*/  PINICACHE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_GENERIC_WRITE ; 
 int FILE_NON_DIRECTORY_FILE ; 
 int FILE_SEQUENTIAL_ONLY ; 
 int /*<<< orphan*/  FILE_SUPERSEDE ; 
 int FILE_SYNCHRONOUS_IO_NONALERT ; 
 int /*<<< orphan*/  IniCacheSaveByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SYNCHRONIZE ; 

NTSTATUS
IniCacheSave(
    PINICACHE Cache,
    PWCHAR FileName)
{
    NTSTATUS Status;
    UNICODE_STRING Name;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE FileHandle;

    /* Create the INI file */
    RtlInitUnicodeString(&Name, FileName);

    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtCreateFile(&FileHandle,
                          FILE_GENERIC_WRITE | SYNCHRONIZE,
                          &ObjectAttributes,
                          &IoStatusBlock,
                          NULL,
                          FILE_ATTRIBUTE_NORMAL,
                          0,
                          FILE_SUPERSEDE,
                          FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY | FILE_NON_DIRECTORY_FILE,
                          NULL,
                          0);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtCreateFile() failed (Status %lx)\n", Status);
        return Status;
    }

    Status = IniCacheSaveByHandle(Cache, FileHandle);

    /* Close the INI file */
    NtClose(FileHandle);
    return Status;
}