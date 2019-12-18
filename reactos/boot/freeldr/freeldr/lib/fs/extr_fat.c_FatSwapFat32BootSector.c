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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PFAT32_BOOTSECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  BackupBootSector ; 
 int /*<<< orphan*/  BootSectorMagic ; 
 int /*<<< orphan*/  BytesPerSector ; 
 int /*<<< orphan*/  ExtendedFlags ; 
 int /*<<< orphan*/  FileSystemVersion ; 
 int /*<<< orphan*/  FsInfo ; 
 int /*<<< orphan*/  HiddenSectors ; 
 int /*<<< orphan*/  NumberOfHeads ; 
 int /*<<< orphan*/  ReservedSectors ; 
 int /*<<< orphan*/  RootDirEntries ; 
 int /*<<< orphan*/  RootDirStartCluster ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SectorsPerFat ; 
 int /*<<< orphan*/  SectorsPerFatBig ; 
 int /*<<< orphan*/  TotalSectors ; 
 int /*<<< orphan*/  TotalSectorsBig ; 
 int /*<<< orphan*/  VolumeSerialNumber ; 

VOID FatSwapFat32BootSector(PFAT32_BOOTSECTOR Obj)
{
    SW(Obj, BytesPerSector);
    SW(Obj, ReservedSectors);
    SW(Obj, RootDirEntries);
    SW(Obj, TotalSectors);
    SW(Obj, SectorsPerFat);
    SW(Obj, NumberOfHeads);
    SD(Obj, HiddenSectors);
    SD(Obj, TotalSectorsBig);
    SD(Obj, SectorsPerFatBig);
    SW(Obj, ExtendedFlags);
    SW(Obj, FileSystemVersion);
    SD(Obj, RootDirStartCluster);
    SW(Obj, FsInfo);
    SW(Obj, BackupBootSector);
    SD(Obj, VolumeSerialNumber);
    SW(Obj, BootSectorMagic);
}