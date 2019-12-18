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
typedef  void* PVOID ;
typedef  void* PFILESYSTEM_STATISTICS ;
typedef  void* PFAT_STATISTICS ;

/* Variables and functions */
 int /*<<< orphan*/  CreateHits ; 
 int /*<<< orphan*/  DUMP_VALUE (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DumpBase (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FailedCreates ; 
 int /*<<< orphan*/  NonCachedDiskReads ; 
 int /*<<< orphan*/  NonCachedDiskWrites ; 
 int /*<<< orphan*/  NonCachedReadBytes ; 
 int /*<<< orphan*/  NonCachedReads ; 
 int /*<<< orphan*/  NonCachedWriteBytes ; 
 int /*<<< orphan*/  NonCachedWrites ; 
 int /*<<< orphan*/  SuccessfulCreates ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static void
DumpFat(PVOID Statistics, PVOID Specific)
{
    PFAT_STATISTICS Fat;
    PFILESYSTEM_STATISTICS Base;

    Base = Statistics;
    Fat = Specific;

    /* First, display the generic stats */
    DumpBase(Base, _T("FAT"));

    /* Then, display the FAT specific ones */
    DUMP_VALUE(Fat, CreateHits);
    DUMP_VALUE(Fat, SuccessfulCreates);
    DUMP_VALUE(Fat, FailedCreates);
    DUMP_VALUE(Fat, NonCachedReads);
    DUMP_VALUE(Fat, NonCachedReadBytes);
    DUMP_VALUE(Fat, NonCachedWrites);
    DUMP_VALUE(Fat, NonCachedWriteBytes);
    DUMP_VALUE(Fat, NonCachedDiskReads);
    DUMP_VALUE(Fat, NonCachedDiskWrites);
}