#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_6__ {int /*<<< orphan*/  ValueLength; } ;
struct TYPE_5__ {int /*<<< orphan*/  DataSize; } ;
struct TYPE_7__ {TYPE_2__ Resident; TYPE_1__ NonResident; scalar_t__ IsNonResident; } ;
typedef  TYPE_3__* PNTFS_ATTR_RECORD ;

/* Variables and functions */

ULONGLONG
AttributeDataLength(PNTFS_ATTR_RECORD AttrRecord)
{
    if (AttrRecord->IsNonResident)
        return AttrRecord->NonResident.DataSize;
    else
        return AttrRecord->Resident.ValueLength;
}