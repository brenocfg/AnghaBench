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
struct regsvr_metadatareader {struct reader_containers* containers; scalar_t__ requires_fixedsize; int /*<<< orphan*/  supports_padding; int /*<<< orphan*/  requires_fullstream; scalar_t__ version; scalar_t__ specversion; int /*<<< orphan*/ * metadata_format; int /*<<< orphan*/ * vendor; scalar_t__ friendlyname; scalar_t__ author; int /*<<< orphan*/ * clsid; } ;
struct reader_containers {TYPE_1__* patterns; int /*<<< orphan*/ * format; } ;
typedef  char WCHAR ;
struct TYPE_2__ {int length; scalar_t__ data_offset; int /*<<< orphan*/  const* mask; int /*<<< orphan*/  const* pattern; int /*<<< orphan*/  position; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CATID_WICMetadataReader ; 
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
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  author_valuename ; 
 char* clsid_keyname ; 
 int /*<<< orphan*/  clsid_valuename ; 
 char* containers_keyname ; 
 int /*<<< orphan*/  dataoffset_valuename ; 
 int /*<<< orphan*/  friendlyname_valuename ; 
 char* instance_keyname ; 
 int /*<<< orphan*/  mask_valuename ; 
 int /*<<< orphan*/  metadataformat_valuename ; 
 int /*<<< orphan*/  pattern_valuename ; 
 int /*<<< orphan*/  position_valuename ; 
 int /*<<< orphan*/  requiresfixedsize_valuename ; 
 int /*<<< orphan*/  requiresfullstream_valuename ; 
 int /*<<< orphan*/  snprintfW (char*,int,char const*,int) ; 
 int /*<<< orphan*/  specversion_valuename ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  supportspadding_valuename ; 
 int /*<<< orphan*/  vendor_valuename ; 
 int /*<<< orphan*/  version_valuename ; 

__attribute__((used)) static HRESULT register_metadatareaders(struct regsvr_metadatareader const *list)
{
    LONG res = ERROR_SUCCESS;
    HKEY coclass_key;
    WCHAR buf[39];
    HKEY readers_key;
    HKEY instance_key;

    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, clsid_keyname, 0, NULL, 0,
			  KEY_READ | KEY_WRITE, NULL, &coclass_key, NULL);
    if (res == ERROR_SUCCESS)  {
        StringFromGUID2(&CATID_WICMetadataReader, buf, 39);
        res = RegCreateKeyExW(coclass_key, buf, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &readers_key, NULL);
        if (res == ERROR_SUCCESS)
        {
            res = RegCreateKeyExW(readers_key, instance_keyname, 0, NULL, 0,
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

        if (list->metadata_format) {
            StringFromGUID2(list->metadata_format, buf, 39);
	    res = RegSetValueExW(clsid_key, metadataformat_valuename, 0, REG_SZ,
                                 (const BYTE*)buf, 78);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->version) {
	    res = RegSetValueExA(clsid_key, version_valuename, 0, REG_SZ,
                                 (const BYTE*)list->version,
				 strlen(list->version) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->specversion) {
	    res = RegSetValueExA(clsid_key, specversion_valuename, 0, REG_SZ,
                                 (const BYTE*)list->version,
				 strlen(list->version) + 1);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        res = RegSetValueExA(clsid_key, requiresfullstream_valuename, 0, REG_DWORD,
                             (const BYTE*)&list->requires_fullstream, 4);
        if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        res = RegSetValueExA(clsid_key, supportspadding_valuename, 0, REG_DWORD,
                             (const BYTE*)&list->supports_padding, 4);
        if (res != ERROR_SUCCESS) goto error_close_clsid_key;

        if (list->requires_fixedsize) {
	    res = RegSetValueExA(clsid_key, requiresfixedsize_valuename, 0, REG_DWORD,
                                 (const BYTE*)&list->requires_fixedsize, 4);
	    if (res != ERROR_SUCCESS) goto error_close_clsid_key;
        }

        if (list->containers) {
            HKEY containers_key;
            const struct reader_containers *container;

            res = RegCreateKeyExW(clsid_key, containers_keyname, 0, NULL, 0,
                                  KEY_READ | KEY_WRITE, NULL, &containers_key, NULL);
            if (res != ERROR_SUCCESS) goto error_close_clsid_key;
            for (container=list->containers; container->format; ++container)
            {
                HKEY format_key;
                int i;
                StringFromGUID2(container->format, buf, 39);
                res = RegCreateKeyExW(containers_key, buf, 0, NULL, 0,
                                      KEY_READ | KEY_WRITE, NULL, &format_key, NULL);
                if (res != ERROR_SUCCESS) break;

                for (i=0; container->patterns[i].length; i++)
                {
                    HKEY pattern_key;
                    static const WCHAR int_format[] = {'%','i',0};
                    snprintfW(buf, 39, int_format, i);
                    res = RegCreateKeyExW(format_key, buf, 0, NULL, 0,
                                          KEY_READ | KEY_WRITE, NULL, &pattern_key, NULL);
                    if (res != ERROR_SUCCESS) break;
                    res = RegSetValueExA(pattern_key, position_valuename, 0, REG_DWORD,
                                         (const BYTE*)&container->patterns[i].position, 4);
                    if (res == ERROR_SUCCESS)
                        res = RegSetValueExA(pattern_key, pattern_valuename, 0, REG_BINARY,
                                             container->patterns[i].pattern,
                                             container->patterns[i].length);
                    if (res == ERROR_SUCCESS)
                        res = RegSetValueExA(pattern_key, mask_valuename, 0, REG_BINARY,
                                             container->patterns[i].mask,
                                             container->patterns[i].length);
                    if (res == ERROR_SUCCESS && container->patterns[i].data_offset)
                        res = RegSetValueExA(pattern_key, dataoffset_valuename, 0, REG_DWORD,
                                             (const BYTE*)&container->patterns[i].data_offset, 4);
                    RegCloseKey(pattern_key);
                }

                RegCloseKey(format_key);
            }
            RegCloseKey(containers_key);
        }

    error_close_clsid_key:
	RegCloseKey(clsid_key);
    }

error_close_coclass_key:
    RegCloseKey(instance_key);
    RegCloseKey(readers_key);
    RegCloseKey(coclass_key);
error_return:
    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}