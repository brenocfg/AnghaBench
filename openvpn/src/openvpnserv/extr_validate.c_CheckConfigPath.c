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
struct TYPE_3__ {int /*<<< orphan*/ * config_dir; } ;
typedef  TYPE_1__ settings_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ PathIsRelativeW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openvpn_swprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int wcslen (int /*<<< orphan*/  const*) ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * wcsstr (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static BOOL
CheckConfigPath(const WCHAR *workdir, const WCHAR *fname, const settings_t *s)
{
    WCHAR tmp[MAX_PATH];
    const WCHAR *config_file = NULL;
    const WCHAR *config_dir = NULL;
#ifndef UNICODE
    WCHAR widepath[MAX_PATH];
#endif

    /* convert fname to full path */
    if (PathIsRelativeW(fname) )
    {
        openvpn_swprintf(tmp, _countof(tmp), L"%s\\%s", workdir, fname);
        config_file = tmp;
    }
    else
    {
        config_file = fname;
    }

#ifdef UNICODE
    config_dir = s->config_dir;
#else
    if (MultiByteToWideChar(CP_UTF8, 0, s->config_dir, -1, widepath, MAX_PATH) == 0)
    {
        MsgToEventLog(M_SYSERR, TEXT("Failed to convert config_dir name to WideChar"));
        return FALSE;
    }
    config_dir = widepath;
#endif

    if (wcsncmp(config_dir, config_file, wcslen(config_dir)) == 0
        && wcsstr(config_file + wcslen(config_dir), L"..") == NULL)
    {
        return TRUE;
    }

    return FALSE;
}