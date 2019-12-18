#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  default_install ;
typedef  char WCHAR ;
struct TYPE_4__ {char const* inf_filename; char const* install_sec; char const* working_dir; char const* inf_path; scalar_t__ hinf; int flags; int /*<<< orphan*/  need_reboot; } ;
typedef  char const* LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_1__ ADVInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ADV_HRESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INF_STYLE_WIN4 ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int RSC_FLAG_INF ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ SetupOpenInfFileW (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_working_dir (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  lstrcatW (char const*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char const*,char const*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  set_ldids (scalar_t__,char const*,char const*) ; 
 char* wcsrchr (char const*,char) ; 

__attribute__((used)) static HRESULT install_init(LPCWSTR inf_filename, LPCWSTR install_sec,
                            LPCWSTR working_dir, DWORD flags, ADVInfo *info)
{
    DWORD len;
    HRESULT hr;
    LPCWSTR ptr, path;

    static const WCHAR backslash[] = {'\\',0};
    static const WCHAR default_install[] = {
        'D','e','f','a','u','l','t','I','n','s','t','a','l','l',0
    };

    if (!(ptr = wcsrchr(inf_filename, '\\')))
        ptr = inf_filename;

    len = lstrlenW(ptr);

    info->inf_filename = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR));
    if (!info->inf_filename)
        return E_OUTOFMEMORY;

    lstrcpyW(info->inf_filename, ptr);

    /* FIXME: determine the proper platform to install (NTx86, etc) */
    if (!install_sec || !*install_sec)
    {
        len = sizeof(default_install) - 1;
        ptr = default_install;
    }
    else
    {
        len = lstrlenW(install_sec);
        ptr = install_sec;
    }

    info->install_sec = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR));
    if (!info->install_sec)
        return E_OUTOFMEMORY;

    lstrcpyW(info->install_sec, ptr);

    hr = get_working_dir(info, inf_filename, working_dir);
    if (FAILED(hr))
        return hr;

    len = lstrlenW(info->working_dir) + lstrlenW(info->inf_filename) + 2;
    info->inf_path = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (!info->inf_path)
        return E_OUTOFMEMORY;

    lstrcpyW(info->inf_path, info->working_dir);
    lstrcatW(info->inf_path, backslash);
    lstrcatW(info->inf_path, info->inf_filename);

    /* RunSetupCommand opens unmodified filename parameter */
    if (flags & RSC_FLAG_INF)
        path = inf_filename;
    else
        path = info->inf_path;

    info->hinf = SetupOpenInfFileW(path, NULL, INF_STYLE_WIN4, NULL);
    if (info->hinf == INVALID_HANDLE_VALUE)
        return ADV_HRESULT(GetLastError());

    set_ldids(info->hinf, info->install_sec, info->working_dir);

    /* FIXME: check that the INF is advanced */

    info->flags = flags;
    info->need_reboot = FALSE;

    return S_OK;
}