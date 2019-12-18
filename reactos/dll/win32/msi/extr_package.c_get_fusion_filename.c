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
typedef  int /*<<< orphan*/  path ;
typedef  float WCHAR ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  float* LPWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetFileAttributesW (float*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (float*,int) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  KEY_CREATE_SUB_KEY ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,float const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (float*) ; 
 float* msi_alloc (int) ; 
 int /*<<< orphan*/  strcatW (float*,float const*) ; 
 int /*<<< orphan*/  strcpyW (float*,float*) ; 
 int strlenW (float const*) ; 
 float const* szBackSlash ; 

__attribute__((used)) static LPWSTR get_fusion_filename(MSIPACKAGE *package)
{
    static const WCHAR fusion[] =
        {'f','u','s','i','o','n','.','d','l','l',0};
    static const WCHAR subkey[] =
        {'S','o','f','t','w','a','r','e','\\','M','i','c','r','o','s','o','f','t','\\',
         'N','E','T',' ','F','r','a','m','e','w','o','r','k',' ','S','e','t','u','p','\\','N','D','P',0};
    static const WCHAR subdir[] =
        {'M','i','c','r','o','s','o','f','t','.','N','E','T','\\','F','r','a','m','e','w','o','r','k','\\',0};
    static const WCHAR v2050727[] =
        {'v','2','.','0','.','5','0','7','2','7',0};
    static const WCHAR v4client[] =
        {'v','4','\\','C','l','i','e','n','t',0};
    static const WCHAR installpath[] =
        {'I','n','s','t','a','l','l','P','a','t','h',0};
    HKEY netsetup, hkey;
    LONG res;
    DWORD size, len, type;
    WCHAR windir[MAX_PATH], path[MAX_PATH], *filename = NULL;

    res = RegOpenKeyExW(HKEY_LOCAL_MACHINE, subkey, 0, KEY_CREATE_SUB_KEY, &netsetup);
    if (res != ERROR_SUCCESS)
        return NULL;

    if (!RegCreateKeyExW(netsetup, v4client, 0, NULL, 0, KEY_QUERY_VALUE, NULL, &hkey, NULL))
    {
        size = sizeof(path)/sizeof(path[0]);
        if (!RegQueryValueExW(hkey, installpath, NULL, &type, (BYTE *)path, &size))
        {
            len = strlenW(path) + strlenW(fusion) + 2;
            if (!(filename = msi_alloc(len * sizeof(WCHAR)))) return NULL;

            strcpyW(filename, path);
            strcatW(filename, szBackSlash);
            strcatW(filename, fusion);
            if (GetFileAttributesW(filename) != INVALID_FILE_ATTRIBUTES)
            {
                TRACE( "found %s\n", debugstr_w(filename) );
                RegCloseKey(hkey);
                RegCloseKey(netsetup);
                return filename;
            }
        }
        RegCloseKey(hkey);
    }

    if (!RegCreateKeyExW(netsetup, v2050727, 0, NULL, 0, KEY_QUERY_VALUE, NULL, &hkey, NULL))
    {
        RegCloseKey(hkey);
        GetWindowsDirectoryW(windir, MAX_PATH);
        len = strlenW(windir) + strlenW(subdir) + strlenW(v2050727) + strlenW(fusion) + 3;
        if (!(filename = msi_alloc(len * sizeof(WCHAR)))) return NULL;

        strcpyW(filename, windir);
        strcatW(filename, szBackSlash);
        strcatW(filename, subdir);
        strcatW(filename, v2050727);
        strcatW(filename, szBackSlash);
        strcatW(filename, fusion);
        if (GetFileAttributesW(filename) != INVALID_FILE_ATTRIBUTES)
        {
            TRACE( "found %s\n", debugstr_w(filename) );
            RegCloseKey(netsetup);
            return filename;
        }
    }

    RegCloseKey(netsetup);
    return filename;
}