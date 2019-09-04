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
typedef  void* PEXFAT_STATISTICS ;

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
DumpExFat(PVOID Statistics, PVOID Specific)
{
    PEXFAT_STATISTICS ExFat;
    PFILESYSTEM_STATISTICS Base;

    Base = Statistics;
    ExFat = Specific;

    /* First, display the generic stats */
    DumpBase(Base, _T("EXFAT"));

    /* Then, display the EXFAT specific ones */
    DUMP_VALUE(ExFat, CreateHits);
    DUMP_VALUE(ExFat, SuccessfulCreates);
    DUMP_VALUE(ExFat, FailedCreates);
    DUMP_VALUE(ExFat, NonCachedReads);
    DUMP_VALUE(ExFat, NonCachedReadBytes);
    DUMP_VALUE(ExFat, NonCachedWrites);
    DUMP_VALUE(ExFat, NonCachedWriteBytes);
    DUMP_VALUE(ExFat, NonCachedDiskReads);
    DUMP_VALUE(ExFat, NonCachedDiskWrites);
}