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
typedef  void* PNTFS_STATISTICS ;
typedef  void* PFILESYSTEM_STATISTICS ;

/* Variables and functions */
 int /*<<< orphan*/  BitmapReadBytes ; 
 int /*<<< orphan*/  BitmapReads ; 
 int /*<<< orphan*/  BitmapWriteBytes ; 
 int /*<<< orphan*/  BitmapWrites ; 
 int /*<<< orphan*/  DUMP_VALUE (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DumpBase (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogFileReadBytes ; 
 int /*<<< orphan*/  LogFileReads ; 
 int /*<<< orphan*/  LogFileWriteBytes ; 
 int /*<<< orphan*/  LogFileWrites ; 
 int /*<<< orphan*/  Mft2WriteBytes ; 
 int /*<<< orphan*/  Mft2Writes ; 
 int /*<<< orphan*/  MftBitmapReadBytes ; 
 int /*<<< orphan*/  MftBitmapReads ; 
 int /*<<< orphan*/  MftBitmapWriteBytes ; 
 int /*<<< orphan*/  MftBitmapWrites ; 
 int /*<<< orphan*/  MftReadBytes ; 
 int /*<<< orphan*/  MftReads ; 
 int /*<<< orphan*/  MftWriteBytes ; 
 int /*<<< orphan*/  MftWrites ; 
 int /*<<< orphan*/  RootIndexReadBytes ; 
 int /*<<< orphan*/  RootIndexReads ; 
 int /*<<< orphan*/  RootIndexWriteBytes ; 
 int /*<<< orphan*/  RootIndexWrites ; 
 int /*<<< orphan*/  UserIndexReadBytes ; 
 int /*<<< orphan*/  UserIndexReads ; 
 int /*<<< orphan*/  UserIndexWriteBytes ; 
 int /*<<< orphan*/  UserIndexWrites ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static void
DumpNtfs(PVOID Statistics, PVOID Specific)
{
    PNTFS_STATISTICS Ntfs;
    PFILESYSTEM_STATISTICS Base;

    Base = Statistics;
    Ntfs = Specific;

    /* First, display the generic stats */
    DumpBase(Base, _T("NTFS"));

    /* Then, display the NTFS specific ones */
    DUMP_VALUE(Ntfs, MftReads);
    DUMP_VALUE(Ntfs, MftReadBytes);
    DUMP_VALUE(Ntfs, MftWrites);
    DUMP_VALUE(Ntfs, MftWriteBytes);
    DUMP_VALUE(Ntfs, Mft2Writes);
    DUMP_VALUE(Ntfs, Mft2WriteBytes);
    DUMP_VALUE(Ntfs, RootIndexReads);
    DUMP_VALUE(Ntfs, RootIndexReadBytes);
    DUMP_VALUE(Ntfs, RootIndexWrites);
    DUMP_VALUE(Ntfs, RootIndexWriteBytes);
    DUMP_VALUE(Ntfs, BitmapReads);
    DUMP_VALUE(Ntfs, BitmapReadBytes);
    DUMP_VALUE(Ntfs, BitmapWrites);
    DUMP_VALUE(Ntfs, BitmapWriteBytes);
    DUMP_VALUE(Ntfs, MftBitmapReads);
    DUMP_VALUE(Ntfs, MftBitmapReadBytes);
    DUMP_VALUE(Ntfs, MftBitmapWrites);
    DUMP_VALUE(Ntfs, MftBitmapWriteBytes);
    DUMP_VALUE(Ntfs, UserIndexReads);
    DUMP_VALUE(Ntfs, UserIndexReadBytes);
    DUMP_VALUE(Ntfs, UserIndexWrites);
    DUMP_VALUE(Ntfs, UserIndexWriteBytes);
    DUMP_VALUE(Ntfs, LogFileReads);
    DUMP_VALUE(Ntfs, LogFileReadBytes);
    DUMP_VALUE(Ntfs, LogFileWrites);
    DUMP_VALUE(Ntfs, LogFileWriteBytes);
}