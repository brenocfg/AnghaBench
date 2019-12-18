#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
struct TYPE_3__ {int Version; int SizeOfCompleteStructure; int /*<<< orphan*/  FileSystemType; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ FILESYSTEM_STATISTICS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM_STATISTICS_TYPE_NTFS ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static NTSTATUS fs_get_statistics(void* buffer, DWORD buflen, ULONG_PTR* retlen) {
    FILESYSTEM_STATISTICS* fss;

    WARN("STUB: FSCTL_FILESYSTEM_GET_STATISTICS\n");

    // This is hideously wrong, but at least it stops SMB from breaking

    if (buflen < sizeof(FILESYSTEM_STATISTICS))
        return STATUS_BUFFER_TOO_SMALL;

    fss = buffer;
    RtlZeroMemory(fss, sizeof(FILESYSTEM_STATISTICS));

    fss->Version = 1;
    fss->FileSystemType = FILESYSTEM_STATISTICS_TYPE_NTFS;
    fss->SizeOfCompleteStructure = sizeof(FILESYSTEM_STATISTICS);

    *retlen = sizeof(FILESYSTEM_STATISTICS);

    return STATUS_SUCCESS;
}