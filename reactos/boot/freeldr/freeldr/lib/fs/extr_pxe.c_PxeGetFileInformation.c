#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_6__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_8__ {TYPE_2__ CurrentAddress; TYPE_1__ EndingAddress; } ;
typedef  TYPE_3__ FILEINFORMATION ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  ESUCCESS ; 
 scalar_t__ NO_FILE ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FilePosition ; 
 int /*<<< orphan*/  _FileSize ; 
 scalar_t__ _OpenFile ; 

__attribute__((used)) static ARC_STATUS PxeGetFileInformation(ULONG FileId, FILEINFORMATION* Information)
{
    if (_OpenFile == NO_FILE || FileId != _OpenFile)
        return EBADF;

    RtlZeroMemory(Information, sizeof(*Information));
    Information->EndingAddress.LowPart = _FileSize;
    Information->CurrentAddress.LowPart = _FilePosition;

    TRACE("PxeGetFileInformation(%lu) -> FileSize = %lu, FilePointer = 0x%lx\n",
          FileId, Information->EndingAddress.LowPart, Information->CurrentAddress.LowPart);

    return ESUCCESS;
}