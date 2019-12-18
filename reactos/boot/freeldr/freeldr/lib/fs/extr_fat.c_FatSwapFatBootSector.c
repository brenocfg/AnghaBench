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
typedef  int /*<<< orphan*/  PFAT_BOOTSECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  BootSectorMagic ; 
 int /*<<< orphan*/  BytesPerSector ; 
 int /*<<< orphan*/  HiddenSectors ; 
 int /*<<< orphan*/  NumberOfHeads ; 
 int /*<<< orphan*/  ReservedSectors ; 
 int /*<<< orphan*/  RootDirEntries ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SectorsPerFat ; 
 int /*<<< orphan*/  SectorsPerTrack ; 
 int /*<<< orphan*/  TotalSectors ; 
 int /*<<< orphan*/  TotalSectorsBig ; 
 int /*<<< orphan*/  VolumeSerialNumber ; 

VOID FatSwapFatBootSector(PFAT_BOOTSECTOR Obj)
{
    SW(Obj, BytesPerSector);
    SW(Obj, ReservedSectors);
    SW(Obj, RootDirEntries);
    SW(Obj, TotalSectors);
    SW(Obj, SectorsPerFat);
    SW(Obj, SectorsPerTrack);
    SW(Obj, NumberOfHeads);
    SD(Obj, HiddenSectors);
    SD(Obj, TotalSectorsBig);
    SD(Obj, VolumeSerialNumber);
    SW(Obj, BootSectorMagic);
}