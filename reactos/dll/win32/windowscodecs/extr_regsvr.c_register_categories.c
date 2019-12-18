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
struct regsvr_category {int /*<<< orphan*/ * clsid; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WICImagingCategories ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * clsid_keyname ; 
 int /*<<< orphan*/  clsid_valuename ; 
 int /*<<< orphan*/ * instance_keyname ; 

__attribute__((used)) static HRESULT register_categories(const struct regsvr_category *list)
{
    LONG res;
    WCHAR buf[39];
    HKEY coclass_key, categories_key, instance_key;

    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, clsid_keyname, 0, NULL, 0,
                          KEY_READ | KEY_WRITE, NULL, &coclass_key, NULL);
    if (res != ERROR_SUCCESS) return HRESULT_FROM_WIN32(res);

    StringFromGUID2(&CLSID_WICImagingCategories, buf, 39);
    res = RegCreateKeyExW(coclass_key, buf, 0, NULL, 0,
                          KEY_READ | KEY_WRITE, NULL, &categories_key, NULL);
    if (res != ERROR_SUCCESS)
    {
        RegCloseKey(coclass_key);
        return HRESULT_FROM_WIN32(res);
    }

    res = RegCreateKeyExW(categories_key, instance_keyname, 0, NULL, 0,
                          KEY_READ | KEY_WRITE, NULL, &instance_key, NULL);

    for (; res == ERROR_SUCCESS && list->clsid; list++)
    {
        HKEY instance_clsid_key;

        StringFromGUID2(list->clsid, buf, 39);
        res = RegCreateKeyExW(instance_key, buf, 0, NULL, 0,
                              KEY_READ | KEY_WRITE, NULL, &instance_clsid_key, NULL);
        if (res == ERROR_SUCCESS)
        {
            res = RegSetValueExW(instance_clsid_key, clsid_valuename, 0, REG_SZ,
                                 (const BYTE *)buf, 78);
            RegCloseKey(instance_clsid_key);
        }
    }

    RegCloseKey(instance_key);
    RegCloseKey(categories_key);
    RegCloseKey(coclass_key);

    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}