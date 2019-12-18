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
struct regsvr_mediatype_parsing {scalar_t__* line; int /*<<< orphan*/ * subtype; int /*<<< orphan*/ * majortype; } ;
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
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lstrlenA (scalar_t__) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mediatype_name ; 
 int /*<<< orphan*/  sourcefilter_valuename ; 
 int /*<<< orphan*/  wsprintfA (char*,char*,int) ; 

__attribute__((used)) static HRESULT register_mediatypes_parsing(struct regsvr_mediatype_parsing const *list)
{
    LONG res = ERROR_SUCCESS;
    HKEY mediatype_key;
    WCHAR buf[39];
    int i;

    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, mediatype_name, 0, NULL, 0,
			  KEY_READ | KEY_WRITE, NULL, &mediatype_key, NULL);
    if (res != ERROR_SUCCESS) return HRESULT_FROM_WIN32(res);

    for (; res == ERROR_SUCCESS && list->majortype; ++list) {
	HKEY majortype_key = NULL;
	HKEY subtype_key = NULL;

	StringFromGUID2(list->majortype, buf, 39);
	res = RegCreateKeyExW(mediatype_key, buf, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &majortype_key, NULL);
	if (res != ERROR_SUCCESS) goto error_close_keys;

	StringFromGUID2(list->subtype, buf, 39);
	res = RegCreateKeyExW(majortype_key, buf, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &subtype_key, NULL);
	if (res != ERROR_SUCCESS) goto error_close_keys;

	StringFromGUID2(&CLSID_AsyncReader, buf, 39);
        res = RegSetValueExW(subtype_key, sourcefilter_valuename, 0, REG_SZ, (const BYTE*)buf,
			     (lstrlenW(buf) + 1) * sizeof(WCHAR));
	if (res != ERROR_SUCCESS) goto error_close_keys;

	for(i = 0; list->line[i]; i++) {
	    char buffer[3];
	    wsprintfA(buffer, "%d", i);
            res = RegSetValueExA(subtype_key, buffer, 0, REG_SZ, (const BYTE*)list->line[i],
				 lstrlenA(list->line[i]));
	    if (res != ERROR_SUCCESS) goto error_close_keys;
	}

error_close_keys:
	if (majortype_key)
	    RegCloseKey(majortype_key);
	if (subtype_key)
	    RegCloseKey(subtype_key);
    }

    RegCloseKey(mediatype_key);

    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}