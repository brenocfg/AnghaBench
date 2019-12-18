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
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegRestoreKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_BACKUP_NAME ; 
 int /*<<< orphan*/  SE_RESTORE_NAME ; 
 int /*<<< orphan*/  STRING_FUNC_HELP ; 
 int /*<<< orphan*/  STRING_INVALID_KEY ; 
 int /*<<< orphan*/  STRING_INVALID_SYNTAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  output_error (scalar_t__) ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  parse_registry_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_privilege (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struprW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int reg_restore(int argc, WCHAR* argv[])
{
    HKEY root, hkey;
    LSTATUS status;
    WCHAR* path, * long_key;

    if (argc != 4) goto error;

    if (!parse_registry_key(argv[2], &root, &path, &long_key))
        return 1;

    if (RegOpenKeyExW(root, path, 0, KEY_READ, &hkey))
    {
        output_message(STRING_INVALID_KEY);
        return 1;
    }

    if (!set_privilege(SE_BACKUP_NAME, TRUE)) return 1;
    if (!set_privilege(SE_RESTORE_NAME, TRUE)) return 1;

    status = RegRestoreKeyW(hkey, argv[3], 0);
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