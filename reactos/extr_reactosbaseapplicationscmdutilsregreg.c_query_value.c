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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_SUBKEY_LEN ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,char*,int*) ; 
 int /*<<< orphan*/  STRING_CANNOT_FIND ; 
 char* build_subkey_path (char*,int,char*,int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_xalloc (int) ; 
 char* heap_xrealloc (char*,int) ; 
 int /*<<< orphan*/  newlineW ; 
 int /*<<< orphan*/  num_values_found ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_string (char*,...) ; 
 int /*<<< orphan*/  output_value (char*,int,char*,int) ; 
 int strlenW (char*) ; 

__attribute__((used)) static int query_value(HKEY key, WCHAR *value_name, WCHAR *path, BOOL recurse)
{
    LONG rc;
    DWORD max_data_bytes = 2048, data_size;
    DWORD subkey_len;
    DWORD type, path_len, i;
    BYTE *data;
    WCHAR fmt[] = {'%','1','\n',0};
    WCHAR *subkey_name, *subkey_path;
    HKEY subkey;

    data = heap_xalloc(max_data_bytes);

    for (;;)
    {
        data_size = max_data_bytes;
        rc = RegQueryValueExW(key, value_name, NULL, &type, data, &data_size);
        if (rc == ERROR_MORE_DATA)
        {
            max_data_bytes = data_size;
            data = heap_xrealloc(data, max_data_bytes);
        }
        else break;
    }

    if (rc == ERROR_SUCCESS)
    {
        output_string(fmt, path);
        output_value(value_name, type, data, data_size);
        output_string(newlineW);
        num_values_found++;
    }

    heap_free(data);

    if (!recurse)
    {
        if (rc == ERROR_FILE_NOT_FOUND)
        {
            if (value_name && *value_name)
            {
                output_message(STRING_CANNOT_FIND);
                return 1;
            }
            output_string(fmt, path);
            output_value(NULL, REG_SZ, NULL, 0);
        }
        return 0;
    }

    subkey_name = heap_xalloc(MAX_SUBKEY_LEN * sizeof(WCHAR));

    path_len = strlenW(path);

    i = 0;
    for (;;)
    {
        subkey_len = MAX_SUBKEY_LEN;
        rc = RegEnumKeyExW(key, i, subkey_name, &subkey_len, NULL, NULL, NULL, NULL);
        if (rc == ERROR_SUCCESS)
        {
            subkey_path = build_subkey_path(path, path_len, subkey_name, subkey_len);
            if (!RegOpenKeyExW(key, subkey_name, 0, KEY_READ, &subkey))
            {
                query_value(subkey, value_name, subkey_path, recurse);
                RegCloseKey(subkey);
            }
            heap_free(subkey_path);
            i++;
        }
        else break;
    }

    heap_free(subkey_name);
    return 0;
}