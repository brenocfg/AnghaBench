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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
#define  DRIVE_CDROM 134 
#define  DRIVE_FIXED 133 
#define  DRIVE_NO_ROOT_DIR 132 
#define  DRIVE_RAMDISK 131 
#define  DRIVE_REMOTE 130 
#define  DRIVE_REMOVABLE 129 
#define  DRIVE_UNKNOWN 128 
 int GetDriveType (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
DriveTypeMain(int argc, const TCHAR *argv[])
{
    UINT Type;

    /* We need a volume (letter) */
    if (argc < 2)
    {
        _ftprintf(stderr, _T("Usage: fsutil fsinfo drivetype <volume>\n"));
        _ftprintf(stderr, _T("\tFor example: fsutil fsinfo drivetype c:\n"));
        return 1;
    }

    /* Get its drive type and make it readable */
    Type = GetDriveType(argv[1]);
    switch (Type)
    {
        case DRIVE_UNKNOWN:
            _ftprintf(stdout, _T("%s - unknown drive type\n"), argv[1]);
            break;

        case DRIVE_NO_ROOT_DIR:
            _ftprintf(stdout, _T("%s - not a root directory\n"), argv[1]);
            break;

        case DRIVE_REMOVABLE:
            _ftprintf(stdout, _T("%s - removable drive\n"), argv[1]);
            break;

        case DRIVE_FIXED:
            _ftprintf(stdout, _T("%s - fixed drive\n"), argv[1]);
            break;

        case DRIVE_REMOTE:
            _ftprintf(stdout, _T("%s - remote or network drive\n"), argv[1]);
            break;

        case DRIVE_CDROM:
            _ftprintf(stdout, _T("%s - CD-ROM drive\n"), argv[1]);
            break;

        case DRIVE_RAMDISK:
            _ftprintf(stdout, _T("%s - RAM disk drive\n"), argv[1]);
            break;
    }

    return 0;
}