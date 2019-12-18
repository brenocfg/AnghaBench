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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  CLSIDFromProgID (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static BOOL get_engine_clsid(const WCHAR *ext, CLSID *clsid)
{
    WCHAR fileid[64], progid[64];
    DWORD res;
    LONG size;
    HKEY hkey;
    HRESULT hres;

    static const WCHAR script_engineW[] =
        {'\\','S','c','r','i','p','t','E','n','g','i','n','e',0};

    res = RegOpenKeyW(HKEY_CLASSES_ROOT, ext, &hkey);
    if(res != ERROR_SUCCESS)
        return FALSE;

    size = ARRAY_SIZE(fileid);
    res = RegQueryValueW(hkey, NULL, fileid, &size);
    RegCloseKey(hkey);
    if(res != ERROR_SUCCESS)
        return FALSE;

    WINE_TRACE("fileid is %s\n", wine_dbgstr_w(fileid));

    strcatW(fileid, script_engineW);
    res = RegOpenKeyW(HKEY_CLASSES_ROOT, fileid, &hkey);
    if(res != ERROR_SUCCESS)
        return FALSE;

    size = ARRAY_SIZE(progid);
    res = RegQueryValueW(hkey, NULL, progid, &size);
    RegCloseKey(hkey);
    if(res != ERROR_SUCCESS)
        return FALSE;

    WINE_TRACE("ProgID is %s\n", wine_dbgstr_w(progid));

    hres = CLSIDFromProgID(progid, clsid);
    return SUCCEEDED(hres);
}