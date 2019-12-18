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
struct regsvr_pixelformat {int bitsperpixel; size_t channelcount; int /*<<< orphan*/  const** channelmasks; int /*<<< orphan*/  supportsalpha; int /*<<< orphan*/  numericrepresentation; scalar_t__ version; int /*<<< orphan*/ * vendor; scalar_t__ friendlyname; scalar_t__ author; int /*<<< orphan*/ * clsid; } ;
typedef  char WCHAR ;
typedef  size_t UINT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CATID_WICPixelFormats ; 
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
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  author_valuename ; 
 int /*<<< orphan*/  bitsperpixel_valuename ; 
 int /*<<< orphan*/  channelcount_valuename ; 
 char* channelmasks_keyname ; 
 char* clsid_keyname ; 
 char* clsid_valuename ; 
 int /*<<< orphan*/  friendlyname_valuename ; 
 char* instance_keyname ; 
 int /*<<< orphan*/  numericrepresentation_valuename ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,size_t) ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  supportstransparency_valuename ; 
 char* vendor_valuename ; 
 int /*<<< orphan*/  version_valuename ; 

__attribute__((used)) static HRESULT register_pixelformats(struct regsvr_pixelformat const *list)
{
    LONG res = ERROR_SUCCESS;
    HKEY coclass_key;
    WCHAR buf[39];
    HKEY formats_key;
    HKEY instance_key;

    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, clsid_keyname, 0, NULL, 0,
                          KEY_READ | KEY_WRITE, NULL, &coclass_key, NULL);
    if (res == ERROR_SUCCESS)  {
        StringFromGUID2(&CATID_WICPixelFormats, buf, 39);
        res = RegCreateKeyExW(coclass_key, buf, 0, NULL, 0,
                              KEY_READ | KEY_WRITE, NULL, &formats_key, NULL);
        if (res == ERROR_SUCCESS)
        {
            res = RegCreateKeyExW(formats_key, instance_keyname, 0, NULL, 0,
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

        if (list->version) {
            res = RegSetValueExA(clsid_key, version_valuename, 0, REG_SZ,
                                 (const BYTE*)list->version,
                                 strlen(list->version) + 1);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        res = RegSetValueExA(clsid_key, bitsperpixel_valuename, 0, REG_DWORD,
                             (const BYTE*)&list->bitsperpixel, 4);
        if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        res = RegSetValueExA(clsid_key, channelcount_valuename, 0, REG_DWORD,
                             (const BYTE*)&list->channelcount, 4);
        if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        res = RegSetValueExA(clsid_key, numericrepresentation_valuename, 0, REG_DWORD,
                             (const BYTE*)&list->numericrepresentation, 4);
        if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        res = RegSetValueExA(clsid_key, supportstransparency_valuename, 0, REG_DWORD,
                             (const BYTE*)&list->supportsalpha, 4);
        if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        if (list->channelmasks) {
            static const WCHAR valuename_format[] = {'%','d',0};
            HKEY masks_key;
            UINT i, mask_size;
            WCHAR mask_valuename[11];

            mask_size = (list->bitsperpixel + 7)/8;

            res = RegCreateKeyExW(clsid_key, channelmasks_keyname, 0, NULL, 0,
                                  KEY_READ | KEY_WRITE, NULL, &masks_key, NULL);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
            for (i=0; i < list->channelcount; i++)
            {
                sprintfW(mask_valuename, valuename_format, i);
                res = RegSetValueExW(masks_key, mask_valuename, 0, REG_BINARY,
                                     list->channelmasks[i], mask_size);
                if (res != ERROR_SUCCESS) break;
            }
            RegCloseKey(masks_key);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

    error_close_clsid_key:
        RegCloseKey(clsid_key);
    }

error_close_coclass_key:
    RegCloseKey(instance_key);
    RegCloseKey(formats_key);
    RegCloseKey(coclass_key);
error_return:
    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}