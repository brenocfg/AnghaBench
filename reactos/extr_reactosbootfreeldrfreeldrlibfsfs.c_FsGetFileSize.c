#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {scalar_t__ HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_5__ {TYPE_1__ EndingAddress; } ;
typedef  int /*<<< orphan*/  PFILE ;
typedef  TYPE_2__ FILEINFORMATION ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ ArcGetFileInformation (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ESUCCESS ; 

ULONG FsGetFileSize(PFILE FileHandle)
{
    ULONG FileId = (ULONG)FileHandle;
    FILEINFORMATION Information;
    ARC_STATUS Status;

    //
    // Query file informations
    //
    Status = ArcGetFileInformation(FileId, &Information);

    //
    // Check for error
    //
    if (Status != ESUCCESS || Information.EndingAddress.HighPart != 0)
        return 0;

    //
    // Return file size
    //
    return Information.EndingAddress.LowPart;
}