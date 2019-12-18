#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regsvr_decoder {int const* const clsid; int const* const vendor; int const* const container_format; int** formats; TYPE_1__* patterns; scalar_t__ extensions; scalar_t__ mimetypes; scalar_t__ version; scalar_t__ friendlyname; scalar_t__ author; } ;
typedef  char WCHAR ;
struct TYPE_2__ {int length; int /*<<< orphan*/  endofstream; int /*<<< orphan*/  const* mask; int /*<<< orphan*/  const* pattern; int /*<<< orphan*/  position; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int const CATID_WICBitmapDecoders ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int const* const,char*,int) ; 
 int /*<<< orphan*/  author_valuename ; 
 char* clsid_keyname ; 
 int /*<<< orphan*/  clsid_valuename ; 
 int /*<<< orphan*/  containerformat_valuename ; 
 int /*<<< orphan*/  endofstream_valuename ; 
 int /*<<< orphan*/  extensions_valuename ; 
 char* formats_keyname ; 
 int /*<<< orphan*/  friendlyname_valuename ; 
 char* instance_keyname ; 
 int /*<<< orphan*/  length_valuename ; 
 int /*<<< orphan*/  mask_valuename ; 
 int /*<<< orphan*/  mimetypes_valuename ; 
 int /*<<< orphan*/  pattern_valuename ; 
 char* patterns_keyname ; 
 int /*<<< orphan*/  position_valuename ; 
 int /*<<< orphan*/  snprintfW (char*,int,char const*,int) ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  vendor_valuename ; 
 int /*<<< orphan*/  version_valuename ; 

__attribute__((used)) static HRESULT register_decoders(struct regsvr_decoder const *list)
{
    LONG res = ERROR_SUCCESS;
    HKEY coclass_key;
    WCHAR buf[39];
    HKEY decoders_key;
    HKEY instance_key;

    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, clsid_keyname, 0, NULL, 0,
			  KEY_READ | KEY_WRITE, NULL, &coclass_key, NULL);
    if (res == ERROR_SUCCESS)  {
        StringFromGUID2(&CATID_WICBitmapDecoders, buf, 39);
        res = RegCreateKeyExW(coclass_key, buf, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &decoders_key, NULL);
        if (res == ERROR_SUCCESS)
        {
            res = RegCreateKeyExW(decoders_key, instance_keyname, 0, NULL, 0,
		              KEY_READ | KEY_WRITE, NULL, &instance_key, NULL);
            if (res != ERROR_SUCCESS) goto error_close_coclass_key;
        }
        if (res != ERROR_SUCCESS)
            RegCloseKey(coclass_key);
    }
    if (res != ERROR_SUCCESS) goto error_return;

    for (; res == ERROR_SUCCESS && list->clsid; ++list) {
	HKEY clsid_key;
	HKEY instance_clsid_key;

	StringFromGUID2(list->clsid, buf, 39);
	res = RegCreateKeyExW(coclass_key, buf, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &clsid_key, NULL);
	if (res != ERROR_SUCCESS) goto error_close_coclass_key;

	StringFromGUID2(list->clsid, buf, 39);
	res = RegCreateKeyExW(instance_key, buf, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &instance_clsid_key, NULL);
	if (res == ERROR_SUCCESS) {
	    res = RegSetValueExW(instance_clsid_key, clsid_valuename, 0, REG_SZ,
                                 (const BYTE*)buf, 78);
	    RegCloseKey(instance_clsid_key);
	}
	if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        if (list->author) {
	    res = RegSetValueExA(clsid_key, author_valuename, 0, REG_SZ,
                                 (const BYTE*)list->author,
				 strlen(list->author) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->friendlyname) {
	    res = RegSetValueExA(clsid_key, friendlyname_valuename, 0, REG_SZ,
                                 (const BYTE*)list->friendlyname,
				 strlen(list->friendlyname) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->vendor) {
            StringFromGUID2(list->vendor, buf, 39);
	    res = RegSetValueExW(clsid_key, vendor_valuename, 0, REG_SZ,
                                 (const BYTE*)buf, 78);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->container_format) {
            StringFromGUID2(list->container_format, buf, 39);
	    res = RegSetValueExW(clsid_key, containerformat_valuename, 0, REG_SZ,
                                 (const BYTE*)buf, 78);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->version) {
	    res = RegSetValueExA(clsid_key, version_valuename, 0, REG_SZ,
                                 (const BYTE*)list->version,
				 strlen(list->version) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->mimetypes) {
	    res = RegSetValueExA(clsid_key, mimetypes_valuename, 0, REG_SZ,
                                 (const BYTE*)list->mimetypes,
				 strlen(list->mimetypes) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->extensions) {
	    res = RegSetValueExA(clsid_key, extensions_valuename, 0, REG_SZ,
                                 (const BYTE*)list->extensions,
				 strlen(list->extensions) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->formats) {
            HKEY formats_key;
            GUID const * const *format;

            res = RegCreateKeyExW(clsid_key, formats_keyname, 0, NULL, 0,
                                  KEY_READ | KEY_WRITE, NULL, &formats_key, NULL);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
            for (format=list->formats; *format; ++format)
            {
                HKEY format_key;
                StringFromGUID2(*format, buf, 39);
                res = RegCreateKeyExW(formats_key, buf, 0, NULL, 0,
                                      KEY_READ | KEY_WRITE, NULL, &format_key, NULL);
                if (res != ERROR_SUCCESS) break;
                RegCloseKey(format_key);
            }
            RegCloseKey(formats_key);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->patterns) {
            HKEY patterns_key;
            int i;

            res = RegCreateKeyExW(clsid_key, patterns_keyname, 0, NULL, 0,
                                  KEY_READ | KEY_WRITE, NULL, &patterns_key, NULL);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
            for (i=0; list->patterns[i].length; i++)
            {
                HKEY pattern_key;
                static const WCHAR int_format[] = {'%','i',0};
                snprintfW(buf, 39, int_format, i);
                res = RegCreateKeyExW(patterns_key, buf, 0, NULL, 0,
                                      KEY_READ | KEY_WRITE, NULL, &pattern_key, NULL);
                if (res != ERROR_SUCCESS) break;
	        res = RegSetValueExA(pattern_key, length_valuename, 0, REG_DWORD,
                                     (const BYTE*)&list->patterns[i].length, 4);
                if (res == ERROR_SUCCESS)
	            res = RegSetValueExA(pattern_key, position_valuename, 0, REG_DWORD,
                                         (const BYTE*)&list->patterns[i].position, 4);
                if (res == ERROR_SUCCESS)
	            res = RegSetValueExA(pattern_key, pattern_valuename, 0, REG_BINARY,
				         list->patterns[i].pattern,
				         list->patterns[i].length);
                if (res == ERROR_SUCCESS)
	            res = RegSetValueExA(pattern_key, mask_valuename, 0, REG_BINARY,
				         list->patterns[i].mask,
				         list->patterns[i].length);
                if (res == ERROR_SUCCESS)
	            res = RegSetValueExA(pattern_key, endofstream_valuename, 0, REG_DWORD,
                                         (const BYTE*)&list->patterns[i].endofstream, 4);
                RegCloseKey(pattern_key);
            }
            RegCloseKey(patterns_key);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

    error_close_clsid_key:
	RegCloseKey(clsid_key);
    }

error_close_coclass_key:
    RegCloseKey(instance_key);
    RegCloseKey(decoders_key);
    RegCloseKey(coclass_key);
error_return:
    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}