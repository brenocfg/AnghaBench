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
typedef  int PEKIND ;
typedef  int LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetWindowsDirectoryW (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  lstrcpyW (int,char const*) ; 
#define  peAMD64 131 
#define  peI386 130 
#define  peMSIL 129 
#define  peNone 128 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static BOOL get_assembly_directory(LPWSTR dir, DWORD size, const char *version, PEKIND architecture)
{
    static const WCHAR dotnet[] = {'\\','M','i','c','r','o','s','o','f','t','.','N','E','T','\\',0};
    static const WCHAR gac[] = {'\\','a','s','s','e','m','b','l','y','\\','G','A','C',0};
    static const WCHAR msil[] = {'_','M','S','I','L',0};
    static const WCHAR x86[] = {'_','3','2',0};
    static const WCHAR amd64[] = {'_','6','4',0};
    DWORD len = GetWindowsDirectoryW(dir, size);

    if (!strcmp(version, "v4.0.30319"))
    {
        lstrcpyW(dir + len, dotnet);
        len += ARRAY_SIZE(dotnet) - 1;
        lstrcpyW(dir + len, gac + 1);
        len += ARRAY_SIZE(gac) - 2;
    }
    else
    {
        lstrcpyW(dir + len, gac);
        len += ARRAY_SIZE(gac) - 1;
    }
    switch (architecture)
    {
        case peNone:
            break;

        case peMSIL:
            lstrcpyW(dir + len, msil);
            break;

        case peI386:
            lstrcpyW(dir + len, x86);
            break;

        case peAMD64:
            lstrcpyW(dir + len, amd64);
            break;

        default:
            WARN("unhandled architecture %u\n", architecture);
            return FALSE;
    }
    return TRUE;
}