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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PFILESYSTEM_STATISTICS ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MetaDataDiskReads ; 
 int /*<<< orphan*/  MetaDataDiskWrites ; 
 int /*<<< orphan*/  MetaDataReadBytes ; 
 int /*<<< orphan*/  MetaDataReads ; 
 int /*<<< orphan*/  MetaDataWriteBytes ; 
 int /*<<< orphan*/  MetaDataWrites ; 
 int /*<<< orphan*/  UserDiskReads ; 
 int /*<<< orphan*/  UserDiskWrites ; 
 int /*<<< orphan*/  UserFileReadBytes ; 
 int /*<<< orphan*/  UserFileReads ; 
 int /*<<< orphan*/  UserFileWriteBytes ; 
 int /*<<< orphan*/  UserFileWrites ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
DumpBase(PFILESYSTEM_STATISTICS Base, TCHAR * Name)
{
    /* Print FS name */
    _ftprintf(stdout, _T("File system type: %s\n\n"), Name);

    /* And then, dump any base stat */
    DUMP_VALUE(Base, UserFileReads);
    DUMP_VALUE(Base, UserFileReadBytes);
    DUMP_VALUE(Base, UserDiskReads);
    DUMP_VALUE(Base, UserFileWrites);
    DUMP_VALUE(Base, UserFileWriteBytes);
    DUMP_VALUE(Base, UserDiskWrites);
    DUMP_VALUE(Base, MetaDataReads);
    DUMP_VALUE(Base, MetaDataReadBytes);
    DUMP_VALUE(Base, MetaDataDiskReads);
    DUMP_VALUE(Base, MetaDataWrites);
    DUMP_VALUE(Base, MetaDataWriteBytes);
    DUMP_VALUE(Base, MetaDataDiskWrites);

    _ftprintf(stdout, _T("\n"));
}