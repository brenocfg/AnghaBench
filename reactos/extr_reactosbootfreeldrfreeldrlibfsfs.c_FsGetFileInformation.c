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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PFILE ;
typedef  int /*<<< orphan*/  FILEINFORMATION ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ ArcGetFileInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ESUCCESS ; 

BOOLEAN FsGetFileInformation(PFILE FileHandle, FILEINFORMATION* Information)
{
    ULONG FileId = (ULONG)FileHandle;

    //
    // Get file information
    //
    return (ArcGetFileInformation(FileId, Information) == ESUCCESS);
}