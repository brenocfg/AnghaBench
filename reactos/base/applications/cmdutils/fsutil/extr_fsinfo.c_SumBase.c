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
typedef  int /*<<< orphan*/  PFILESYSTEM_STATISTICS ;

/* Variables and functions */
 int /*<<< orphan*/  MetaDataDiskReads ; 
 int /*<<< orphan*/  MetaDataDiskWrites ; 
 int /*<<< orphan*/  MetaDataReadBytes ; 
 int /*<<< orphan*/  MetaDataReads ; 
 int /*<<< orphan*/  MetaDataWriteBytes ; 
 int /*<<< orphan*/  MetaDataWrites ; 
 int /*<<< orphan*/  SUM_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UserDiskReads ; 
 int /*<<< orphan*/  UserDiskWrites ; 
 int /*<<< orphan*/  UserFileReadBytes ; 
 int /*<<< orphan*/  UserFileReads ; 
 int /*<<< orphan*/  UserFileWriteBytes ; 
 int /*<<< orphan*/  UserFileWrites ; 

inline void
SumBase(PFILESYSTEM_STATISTICS Base, PFILESYSTEM_STATISTICS NextBase)
{
    /* Sum any entry in the generic structures */
    SUM_VALUE(Base, NextBase, UserFileReads);
    SUM_VALUE(Base, NextBase, UserFileReadBytes);
    SUM_VALUE(Base, NextBase, UserDiskReads);
    SUM_VALUE(Base, NextBase, UserFileWrites);
    SUM_VALUE(Base, NextBase, UserFileWriteBytes);
    SUM_VALUE(Base, NextBase, UserDiskWrites);
    SUM_VALUE(Base, NextBase, MetaDataReads);
    SUM_VALUE(Base, NextBase, MetaDataReadBytes);
    SUM_VALUE(Base, NextBase, MetaDataDiskReads);
    SUM_VALUE(Base, NextBase, MetaDataWrites);
    SUM_VALUE(Base, NextBase, MetaDataWriteBytes);
    SUM_VALUE(Base, NextBase, MetaDataDiskWrites);
}