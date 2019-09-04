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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PFILE ;

/* Variables and functions */
 int /*<<< orphan*/  ArcClose (int /*<<< orphan*/ ) ; 

VOID FsCloseFile(PFILE FileHandle)
{
    ULONG FileId = (ULONG)FileHandle;

    //
    // Close the handle. Do not check for error,
    // this function is supposed to always succeed.
    //
    ArcClose(FileId);
}