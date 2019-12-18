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
typedef  int /*<<< orphan*/  buf2 ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int CHARS_IN_GUID ; 
 int /*<<< orphan*/  CO_E_CLASSSTRING ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAXIMUM_ALLOWED ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegQueryValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ guid_from_string (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ open_classes_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT clsid_from_string_reg(LPCOLESTR progid, CLSID *clsid)
{
    static const WCHAR clsidW[] = { '\\','C','L','S','I','D',0 };
    WCHAR buf2[CHARS_IN_GUID];
    LONG buf2len = sizeof(buf2);
    HKEY xhkey;
    WCHAR *buf;

    memset(clsid, 0, sizeof(*clsid));
    buf = HeapAlloc( GetProcessHeap(),0,(lstrlenW(progid)+8) * sizeof(WCHAR) );
    if (!buf) return E_OUTOFMEMORY;
    lstrcpyW( buf, progid );
    lstrcatW( buf, clsidW );
    if (open_classes_key(HKEY_CLASSES_ROOT, buf, MAXIMUM_ALLOWED, &xhkey))
    {
        HeapFree(GetProcessHeap(),0,buf);
        WARN("couldn't open key for ProgID %s\n", debugstr_w(progid));
        return CO_E_CLASSSTRING;
    }
    HeapFree(GetProcessHeap(),0,buf);

    if (RegQueryValueW(xhkey,NULL,buf2,&buf2len))
    {
        RegCloseKey(xhkey);
        WARN("couldn't query clsid value for ProgID %s\n", debugstr_w(progid));
        return CO_E_CLASSSTRING;
    }
    RegCloseKey(xhkey);
    return guid_from_string(buf2, clsid) ? S_OK : CO_E_CLASSSTRING;
}