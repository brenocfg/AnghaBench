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
typedef  int /*<<< orphan*/  PFATX_BOOTSECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  NumberOfFats ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SectorsPerCluster ; 
 int /*<<< orphan*/  VolumeSerialNumber ; 

VOID FatSwapFatXBootSector(PFATX_BOOTSECTOR Obj)
{
    SD(Obj, VolumeSerialNumber);
    SD(Obj, SectorsPerCluster);
    SW(Obj, NumberOfFats);
}