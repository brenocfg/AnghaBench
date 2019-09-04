#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_9__ {scalar_t__ MappingPairsOffset; } ;
struct TYPE_12__ {TYPE_1__ NonResident; } ;
struct TYPE_11__ {int CacheRunStartLCN; int CacheRunLastLCN; scalar_t__ CacheRunCurrentOffset; int /*<<< orphan*/  CacheRunLength; scalar_t__ CacheRun; scalar_t__ CacheRunOffset; TYPE_4__ Record; } ;
struct TYPE_10__ {scalar_t__ IsNonResident; scalar_t__ Length; } ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_2__* PNTFS_ATTR_RECORD ;
typedef  TYPE_3__* PNTFS_ATTR_CONTEXT ;
typedef  int LONGLONG ;

/* Variables and functions */
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* FrLdrTempAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTFS_ATTR_CONTEXT ; 
 scalar_t__ NtfsDecodeRun (scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Record ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_4__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  TAG_NTFS_CONTEXT ; 

__attribute__((used)) static PNTFS_ATTR_CONTEXT NtfsPrepareAttributeContext(PNTFS_ATTR_RECORD AttrRecord)
{
    PNTFS_ATTR_CONTEXT Context;

    Context = FrLdrTempAlloc(FIELD_OFFSET(NTFS_ATTR_CONTEXT, Record) + AttrRecord->Length,
                             TAG_NTFS_CONTEXT);
    RtlCopyMemory(&Context->Record, AttrRecord, AttrRecord->Length);
    if (AttrRecord->IsNonResident)
    {
        LONGLONG DataRunOffset;
        ULONGLONG DataRunLength;

        Context->CacheRun = (PUCHAR)&Context->Record + Context->Record.NonResident.MappingPairsOffset;
        Context->CacheRunOffset = 0;
        Context->CacheRun = NtfsDecodeRun(Context->CacheRun, &DataRunOffset, &DataRunLength);
        Context->CacheRunLength = DataRunLength;
        if (DataRunOffset != -1)
        {
            /* Normal run. */
            Context->CacheRunStartLCN =
            Context->CacheRunLastLCN = DataRunOffset;
        }
        else
        {
            /* Sparse run. */
            Context->CacheRunStartLCN = -1;
            Context->CacheRunLastLCN = 0;
        }
        Context->CacheRunCurrentOffset = 0;
    }

    return Context;
}