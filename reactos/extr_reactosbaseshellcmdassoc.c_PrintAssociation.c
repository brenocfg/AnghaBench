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
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutPrintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/ * cmd_alloc (scalar_t__) ; 
 int /*<<< orphan*/  cmd_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT
PrintAssociation(LPTSTR extension)
{
    DWORD return_val;
    HKEY hKey = NULL, hInsideKey = NULL;

    DWORD fileTypeLength = 0;
    LPTSTR fileType = NULL;

    return_val = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Classes"), 0, KEY_READ, &hKey);

    if (return_val != ERROR_SUCCESS)
        return -1;

    return_val = RegOpenKeyEx(hKey, extension, 0, KEY_READ, &hInsideKey);
    RegCloseKey(hKey);

    if (return_val != ERROR_SUCCESS)
        return 0;

    /* obtain string length */
    return_val = RegQueryValueEx(hInsideKey, NULL, NULL, NULL, NULL, &fileTypeLength);

    if (return_val == ERROR_FILE_NOT_FOUND) /* no default value, don't display */
    {
        RegCloseKey(hInsideKey);
        return 0;
    }

    if (return_val != ERROR_SUCCESS)
    {
        RegCloseKey(hInsideKey);
        return -2;
    }

    fileType = cmd_alloc(fileTypeLength * sizeof(TCHAR));
    if (!fileType)
    {
        WARN("Cannot allocate memory for fileType!\n");
        RegCloseKey(hInsideKey);
        return -2;
    }

    /* obtain actual file type */
    return_val = RegQueryValueEx(hInsideKey, NULL, NULL, NULL, (LPBYTE)fileType, &fileTypeLength);
    RegCloseKey(hInsideKey);

    if (return_val != ERROR_SUCCESS)
    {
        cmd_free(fileType);
        return -2;
    }

    if (fileTypeLength != 0)    /* if there is a default key, display relevant information */
    {
        ConOutPrintf(_T("%s=%s\n"), extension, fileType);
    }

    cmd_free(fileType);
    return 1;
}