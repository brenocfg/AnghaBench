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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_SUBKEY_LEN ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int*,char*,int*) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* build_subkey_path (char*,int,char*,int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_xalloc (int) ; 
 char* heap_xrealloc (char*,int) ; 
 int /*<<< orphan*/  newlineW ; 
 int /*<<< orphan*/  output_string (char*,...) ; 
 int /*<<< orphan*/  output_value (char*,int,char*,int) ; 
 int strlenW (char*) ; 

__attribute__((used)) static int query_all(HKEY key, WCHAR *path, BOOL recurse)
{
    LONG rc;
    DWORD max_value_len = 256, value_len;
    DWORD max_data_bytes = 2048, data_size;
    DWORD subkey_len;
    DWORD i, type, path_len;
    WCHAR fmt[] = {'%','1','\n',0};
    WCHAR fmt_path[] = {'%','1','\\','%','2','\n',0};
    WCHAR *value_name, *subkey_name, *subkey_path;
    BYTE *data;
    HKEY subkey;

    output_string(fmt, path);

    value_name = heap_xalloc(max_value_len * sizeof(WCHAR));
    data = heap_xalloc(max_data_bytes);

    i = 0;
    for (;;)
    {
        value_len = max_value_len;
        data_size = max_data_bytes;
        rc = RegEnumValueW(key, i, value_name, &value_len, NULL, &type, data, &data_size);
        if (rc == ERROR_SUCCESS)
        {
            output_value(value_name, type, data, data_size);
            i++;
        }
        else if (rc == ERROR_MORE_DATA)
        {
            if (data_size > max_data_bytes)
            {
                max_data_bytes = data_size;
                data = heap_xrealloc(data, max_data_bytes);
            }
            else
            {
                max_value_len *= 2;
                value_name = heap_xrealloc(value_name, max_value_len * sizeof(WCHAR));
            }
        }
        else break;
    }

    heap_free(data);
    heap_free(value_name);

    if (i || recurse)
        output_string(newlineW);

    subkey_name = heap_xalloc(MAX_SUBKEY_LEN * sizeof(WCHAR));

    path_len = strlenW(path);

    i = 0;
    for (;;)
    {
        subkey_len = MAX_SUBKEY_LEN;
        rc = RegEnumKeyExW(key, i, subkey_name, &subkey_len, NULL, NULL, NULL, NULL);
        if (rc == ERROR_SUCCESS)
        {
            if (recurse)
            {
                subkey_path = build_subkey_path(path, path_len, subkey_name, subkey_len);
                if (!RegOpenKeyExW(key, subkey_name, 0, KEY_READ, &subkey))
                {
                    query_all(subkey, subkey_path, recurse);
                    RegCloseKey(subkey);
                }
                heap_free(subkey_path);
            }
            else output_string(fmt_path, path, subkey_name);
            i++;
        }
        else break;
    }

    heap_free(subkey_name);

    if (i && !recurse)
        output_string(newlineW);

    return 0;
}