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
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PULONGLONG ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  NTFS_FILE_ROOT ; 
 int /*<<< orphan*/  NtfsLookupFileAt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
NtfsLookupFile(PDEVICE_EXTENSION Vcb,
               PUNICODE_STRING PathName,
               BOOLEAN CaseSensitive,
               PFILE_RECORD_HEADER *FileRecord,
               PULONGLONG MFTIndex)
{
    return NtfsLookupFileAt(Vcb, PathName, CaseSensitive, FileRecord, MFTIndex, NTFS_FILE_ROOT);
}