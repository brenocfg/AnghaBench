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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int LPWSTR ;
typedef  int LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CreateDirectoryW (int,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_FILE_EXISTS ; 
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SHARING_VIOLATION ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int GetTickCount () ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (int,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  memcpy (int,int,int) ; 
 int snprintfW (int,int,char const*,int) ; 
 int /*<<< orphan*/  strcatW (int,char const*) ; 
 int strlenW (int) ; 

UINT msi_create_empty_local_file( LPWSTR path, LPCWSTR suffix )
{
    static const WCHAR szInstaller[] = {
        '\\','I','n','s','t','a','l','l','e','r','\\',0};
    static const WCHAR fmt[] = {'%','x',0};
    DWORD time, len, i, offset;
    HANDLE handle;

    time = GetTickCount();
    GetWindowsDirectoryW( path, MAX_PATH );
    strcatW( path, szInstaller );
    CreateDirectoryW( path, NULL );

    len = strlenW(path);
    for (i = 0; i < 0x10000; i++)
    {
        offset = snprintfW( path + len, MAX_PATH - len, fmt, (time + i) & 0xffff );
        memcpy( path + len + offset, suffix, (strlenW( suffix ) + 1) * sizeof(WCHAR) );
        handle = CreateFileW( path, GENERIC_WRITE, 0, NULL,
                              CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0 );
        if (handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(handle);
            break;
        }
        if (GetLastError() != ERROR_FILE_EXISTS &&
            GetLastError() != ERROR_SHARING_VIOLATION)
            return ERROR_FUNCTION_FAILED;
    }

    return ERROR_SUCCESS;
}