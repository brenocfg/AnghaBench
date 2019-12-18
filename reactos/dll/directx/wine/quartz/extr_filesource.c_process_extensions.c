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
typedef  int /*<<< orphan*/  keying ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPCOLESTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromString (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  KEY_READ ; 
 char* PathFindExtensionW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  mediatype_name ; 
 int /*<<< orphan*/  source_filter_name ; 
 int /*<<< orphan*/  subtype_name ; 

__attribute__((used)) static HRESULT process_extensions(HKEY hkeyExtensions, LPCOLESTR pszFileName, GUID * majorType, GUID * minorType, GUID * sourceFilter)
{
    WCHAR *extension;
    LONG l;
    HKEY hsub;
    WCHAR keying[39];
    DWORD size;

    if (!pszFileName)
        return E_POINTER;

    /* Get the part of the name that matters */
    extension = PathFindExtensionW(pszFileName);
    if (*extension != '.')
        return E_FAIL;

    l = RegOpenKeyExW(hkeyExtensions, extension, 0, KEY_READ, &hsub);
    if (l)
        return E_FAIL;

    if (majorType)
    {
        size = sizeof(keying);
        l = RegQueryValueExW(hsub, mediatype_name, NULL, NULL, (LPBYTE)keying, &size);
        if (!l)
            CLSIDFromString(keying, majorType);
    }

    if (minorType)
    {
        size = sizeof(keying);
        if (!l)
            l = RegQueryValueExW(hsub, subtype_name, NULL, NULL, (LPBYTE)keying, &size);
        if (!l)
            CLSIDFromString(keying, minorType);
    }

    if (sourceFilter)
    {
        size = sizeof(keying);
        if (!l)
            l = RegQueryValueExW(hsub, source_filter_name, NULL, NULL, (LPBYTE)keying, &size);
        if (!l)
            CLSIDFromString(keying, sourceFilter);
    }

    RegCloseKey(hsub);

    if (!l)
        return S_OK;
    return E_FAIL;
}