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
struct regsvr_mediatype_extension {int /*<<< orphan*/ * subtype; int /*<<< orphan*/ * majortype; int /*<<< orphan*/  extension; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_AsyncReader ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/ * HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  extensions_keyname ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mediatype_name ; 
 int /*<<< orphan*/  sourcefilter_valuename ; 
 int /*<<< orphan*/  subtype_valuename ; 

__attribute__((used)) static HRESULT register_mediatypes_extension(struct regsvr_mediatype_extension const *list)
{
    LONG res = ERROR_SUCCESS;
    HKEY mediatype_key;
    HKEY extensions_root_key = NULL;
    WCHAR buf[39];

    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, mediatype_name, 0, NULL, 0,
			  KEY_READ | KEY_WRITE, NULL, &mediatype_key, NULL);
    if (res != ERROR_SUCCESS) return HRESULT_FROM_WIN32(res);

    res = RegCreateKeyExW(mediatype_key, extensions_keyname, 0, NULL, 0,
			  KEY_READ | KEY_WRITE, NULL, &extensions_root_key, NULL);
    if (res != ERROR_SUCCESS) goto error_return;

    for (; res == ERROR_SUCCESS && list->majortype; ++list) {
	HKEY extension_key;

	res = RegCreateKeyExA(extensions_root_key, list->extension, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &extension_key, NULL);
	if (res != ERROR_SUCCESS) break;

	StringFromGUID2(list->majortype, buf, 39);
        res = RegSetValueExW(extension_key, mediatype_name, 0, REG_SZ, (const BYTE*)buf,
			     (lstrlenW(buf) + 1) * sizeof(WCHAR));
	if (res != ERROR_SUCCESS) goto error_close_key;

	StringFromGUID2(list->subtype, buf, 39);
        res = RegSetValueExW(extension_key, subtype_valuename, 0, REG_SZ, (const BYTE*)buf,
			     (lstrlenW(buf) + 1) * sizeof(WCHAR));
	if (res != ERROR_SUCCESS) goto error_close_key;

	StringFromGUID2(&CLSID_AsyncReader, buf, 39);
        res = RegSetValueExW(extension_key, sourcefilter_valuename, 0, REG_SZ, (const BYTE*)buf,
			     (lstrlenW(buf) + 1) * sizeof(WCHAR));
	if (res != ERROR_SUCCESS) goto error_close_key;

error_close_key:
	RegCloseKey(extension_key);
    }

error_return:
    RegCloseKey(mediatype_key);
    if (extensions_root_key)
	RegCloseKey(extensions_root_key);

    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}