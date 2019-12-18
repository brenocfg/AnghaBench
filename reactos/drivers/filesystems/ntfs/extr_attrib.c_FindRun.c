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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
struct TYPE_4__ {scalar_t__ LowestVCN; scalar_t__ HighestVCN; scalar_t__ MappingPairsOffset; } ;
struct TYPE_5__ {TYPE_1__ NonResident; } ;
typedef  scalar_t__ PULONGLONG ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_2__* PNTFS_ATTR_RECORD ;
typedef  int /*<<< orphan*/  PLONGLONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeRun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
FindRun(PNTFS_ATTR_RECORD NresAttr,
        ULONGLONG vcn,
        PULONGLONG lcn,
        PULONGLONG count)
{
    if (vcn < NresAttr->NonResident.LowestVCN || vcn > NresAttr->NonResident.HighestVCN)
        return FALSE;

    DecodeRun((PUCHAR)((ULONG_PTR)NresAttr + NresAttr->NonResident.MappingPairsOffset), (PLONGLONG)lcn, count);

    return TRUE;
}