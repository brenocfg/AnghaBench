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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRING_FUNC_HELP ; 
 int /*<<< orphan*/  STRING_INVALID_KEY ; 
 int /*<<< orphan*/  STRING_INVALID_SYNTAX ; 
 int /*<<< orphan*/  export_file_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_newline (int /*<<< orphan*/ ) ; 
 int export_registry_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_file_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_overwrite_switch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  parse_registry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  struprW (int /*<<< orphan*/ *) ; 

int reg_export(int argc, WCHAR *argv[])
{
    HKEY root, hkey;
    WCHAR *path, *long_key;
    BOOL overwrite_file = FALSE;
    HANDLE hFile;
    int ret;

    if (argc == 3 || argc > 5)
        goto error;

    if (!parse_registry_key(argv[2], &root, &path, &long_key))
        return 1;

    if (argc == 5 && !(overwrite_file = is_overwrite_switch(argv[4])))
        goto error;

    if (RegOpenKeyExW(root, path, 0, KEY_READ, &hkey))
    {
        output_message(STRING_INVALID_KEY);
        return 1;
    }

    hFile = get_file_handle(argv[3], overwrite_file);
    export_file_header(hFile);
    ret = export_registry_data(hFile, hkey, long_key);
    export_newline(hFile);
    CloseHandle(hFile);

    RegCloseKey(hkey);

    return ret;

error:
    output_message(STRING_INVALID_SYNTAX);
    output_message(STRING_FUNC_HELP, struprW(argv[1]));
    return 1;
}