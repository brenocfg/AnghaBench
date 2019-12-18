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

/* Variables and functions */
 int /*<<< orphan*/  BackupBootSector (char*) ; 
 int /*<<< orphan*/  CloseVolume () ; 
 int /*<<< orphan*/  InstallBootSector (char*) ; 
 int /*<<< orphan*/  OpenVolume (char*) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        _tprintf(_T("syntax: install x: [fs_type]\nwhere fs_type is fat or fat32\n"));
        return -1;
    }

    if (!OpenVolume(argv[1]))
    {
        return -1;
    }

    BackupBootSector(argv[1]);

    InstallBootSector(argv[2]);

    _tprintf(_T("You must now copy freeldr.sys & freeldr.ini to %s.\n"), argv[1]);

    CloseVolume();

    return 0;
}