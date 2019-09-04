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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PFILE ;
typedef  int BOOLEAN ;

/* Variables and functions */
 scalar_t__ ArcRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ESUCCESS ; 

BOOLEAN FsReadFile(PFILE FileHandle, ULONG BytesToRead, ULONG* BytesRead, PVOID Buffer)
{
    ULONG FileId = (ULONG)FileHandle;

    //
    // Read the file
    //
    return (ArcRead(FileId, Buffer, BytesToRead, BytesRead) == ESUCCESS);
}