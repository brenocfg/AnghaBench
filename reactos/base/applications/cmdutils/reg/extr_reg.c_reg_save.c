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
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetFileAttributes (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  REG_LATEST_FORMAT ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSaveKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_BACKUP_NAME ; 
 int /*<<< orphan*/  STRING_FUNC_HELP ; 
 int /*<<< orphan*/  STRING_INVALID_KEY ; 
 int /*<<< orphan*/  STRING_INVALID_SYNTAX ; 
 int /*<<< orphan*/  STRING_OVERWRITE_FILE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ask_confirm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_error (scalar_t__) ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  parse_registry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_privilege (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  struprW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reg_save(int argc, WCHAR* argv[]) {
    HKEY root, hkey;
    LSTATUS status;
    WCHAR* path, *long_key;

    if (argc < 4 || argc > 5) goto error;

    if (!parse_registry_key(argv[2], &root, &path, &long_key))
        return 1;

    if (GetFileAttributes(argv[3]) != INVALID_FILE_ATTRIBUTES)
    {
        if (argc == 5 && !strcmpiW(argv[4], L"/y"))
        {
            DeleteFile(argv[3]);
        }
        else
        {
            if (ask_confirm(STRING_OVERWRITE_FILE, argv[3]))
                DeleteFile(argv[3]);
        }
    }

    if (RegOpenKeyExW(root, path, 0, KEY_READ, &hkey))
    {
        output_message(STRING_INVALID_KEY);
        return 1;
    }

    if (!set_privilege(SE_BACKUP_NAME, TRUE)) return 1; 

    status = RegSaveKeyExW(hkey, argv[3], NULL, REG_LATEST_FORMAT);
    RegCloseKey(hkey);

    if (status != ERROR_SUCCESS) {
        output_error(status);
        return 1;
    }

    return 0;

error:
    output_message(STRING_INVALID_SYNTAX);
    output_message(STRING_FUNC_HELP, struprW(argv[1]));
    return 1;
}