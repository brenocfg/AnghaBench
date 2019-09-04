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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  FreeldrPath ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ArcOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MachDiskGetBootPath (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OpenReadOnly ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ARC_STATUS IniOpenIniFile(ULONG* FileId)
{
    CHAR FreeldrPath[MAX_PATH];

    //
    // Create full freeldr.ini path
    //
    MachDiskGetBootPath(FreeldrPath, sizeof(FreeldrPath));
    strcat(FreeldrPath, "\\freeldr.ini");

    // Try to open freeldr.ini
    return ArcOpen(FreeldrPath, OpenReadOnly, FileId);
}