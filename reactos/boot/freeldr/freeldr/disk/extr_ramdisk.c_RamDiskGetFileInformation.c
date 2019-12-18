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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_6__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_8__ {TYPE_2__ CurrentAddress; TYPE_1__ EndingAddress; } ;
typedef  TYPE_3__ FILEINFORMATION ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ESUCCESS ; 
 int /*<<< orphan*/  RamDiskImageLength ; 
 int /*<<< orphan*/  RamDiskOffset ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 

__attribute__((used)) static ARC_STATUS RamDiskGetFileInformation(ULONG FileId, FILEINFORMATION* Information)
{
    RtlZeroMemory(Information, sizeof(*Information));
    Information->EndingAddress.QuadPart = RamDiskImageLength;
    Information->CurrentAddress.QuadPart = RamDiskOffset;

    return ESUCCESS;
}