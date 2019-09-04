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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  LowPart; scalar_t__ HighPart; } ;
typedef  int /*<<< orphan*/  PFILE ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ArcSeek (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekAbsolute ; 

VOID FsSetFilePointer(PFILE FileHandle, ULONG NewFilePointer)
{
    ULONG FileId = (ULONG)FileHandle;
    LARGE_INTEGER Position;

    //
    // Set file position. Do not check for error,
    // this function is supposed to always succeed.
    //
    Position.HighPart = 0;
    Position.LowPart = NewFilePointer;
    ArcSeek(FileId, &Position, SeekAbsolute);
}