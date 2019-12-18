#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  working_dir; } ;
typedef  char const* LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ ADVInfo ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 scalar_t__ GetFileAttributesW (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,char const*,int) ; 
 int lstrlenW (char const*) ; 
 char* wcsrchr (char const*,char) ; 

__attribute__((used)) static HRESULT get_working_dir(ADVInfo *info, LPCWSTR inf_filename, LPCWSTR working_dir)
{
    WCHAR path[MAX_PATH];
    LPCWSTR ptr;
    DWORD len;

    static const WCHAR backslash[] = {'\\',0};
    static const WCHAR inf_dir[] = {'\\','I','N','F',0};

    if ((ptr = wcsrchr(inf_filename, '\\')))
    {
        len = ptr - inf_filename + 1;
        ptr = inf_filename;
    }
    else if (working_dir && *working_dir)
    {
        len = lstrlenW(working_dir) + 1;
        ptr = working_dir;
    }
    else
    {
        GetCurrentDirectoryW(MAX_PATH, path);
        lstrcatW(path, backslash);
        lstrcatW(path, inf_filename);

        /* check if the INF file is in the current directory */
        if (GetFileAttributesW(path) != INVALID_FILE_ATTRIBUTES)
        {
            GetCurrentDirectoryW(MAX_PATH, path);
        }
        else
        {
            /* default to the windows\inf directory if all else fails */
            GetWindowsDirectoryW(path, MAX_PATH);
            lstrcatW(path, inf_dir);
        }

        len = lstrlenW(path) + 1;
        ptr = path;
    }

    info->working_dir = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (!info->working_dir)
        return E_OUTOFMEMORY;

    lstrcpynW(info->working_dir, ptr, len);

    return S_OK;
}