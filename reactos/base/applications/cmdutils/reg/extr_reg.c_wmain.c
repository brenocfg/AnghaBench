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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int REG_ADD ; 
 int REG_DELETE ; 
 int REG_EXPORT ; 
 int REG_IMPORT ; 
 int REG_INVALID ; 
 int REG_QUERY ; 
 int REG_RESTORE ; 
 int REG_SAVE ; 
 int /*<<< orphan*/  STRING_FUNC_HELP ; 
 int STRING_INVALID_CMDLINE ; 
 int /*<<< orphan*/  STRING_INVALID_OPTION ; 
 int STRING_INVALID_SYNTAX ; 
 int STRING_REG_HELP ; 
 int STRING_USAGE ; 
 scalar_t__ TRUE ; 
 int get_operation (char*,int*) ; 
 scalar_t__ is_help_switch (char*) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char const*) ; 
 int /*<<< orphan*/  output_message (int,...) ; 
 int /*<<< orphan*/  parse_registry_key (char*,int /*<<< orphan*/ *,char**,char**) ; 
 int reg_add (int /*<<< orphan*/ ,char*,char*,scalar_t__,char*,char,char*,scalar_t__) ; 
 int reg_delete (int /*<<< orphan*/ ,char*,char*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int reg_export (int,char**) ; 
 int reg_import (char*) ; 
 int reg_query (int /*<<< orphan*/ ,char*,char*,char*,scalar_t__,scalar_t__) ; 
 int reg_restore (int,char**) ; 
 int reg_save (int,char**) ; 
 int strlenW (char*) ; 
 int /*<<< orphan*/  struprW (char*) ; 
 int tolowerW (char) ; 

int wmain(int argc, WCHAR *argvW[])
{
    int i, op, op_help, ret;
    BOOL show_op_help = FALSE;
    static const WCHAR switchVAW[] = {'v','a',0};
    static const WCHAR switchVEW[] = {'v','e',0};
    WCHAR *key_name, *path, *value_name = NULL, *type = NULL, *data = NULL, separator = '\0';
    BOOL value_empty = FALSE, value_all = FALSE, recurse = FALSE, force = FALSE;
    HKEY root;

    if (argc == 1)
    {
        output_message(STRING_INVALID_SYNTAX);
        output_message(STRING_REG_HELP);
        return 1;
    }

    if (is_help_switch(argvW[1]))
    {
        output_message(STRING_USAGE);
        return 0;
    }

    op = get_operation(argvW[1], &op_help);

    if (op == REG_INVALID)
    {
        output_message(STRING_INVALID_OPTION, argvW[1]);
        output_message(STRING_REG_HELP);
        return 1;
    }

    if (argc > 2)
        show_op_help = is_help_switch(argvW[2]);

    if (argc == 2 || ((show_op_help || op == REG_IMPORT) && argc > 3))
    {
        output_message(STRING_INVALID_SYNTAX);
        output_message(STRING_FUNC_HELP, struprW(argvW[1]));
        return 1;
    }
    else if (show_op_help)
    {
        output_message(op_help);
        return 0;
    }

    if (op == REG_IMPORT)
        return reg_import(argvW[2]);

    if (op == REG_EXPORT)
        return reg_export(argc, argvW);

    if (op == REG_SAVE)
        return reg_save(argc, argvW);

    if (op == REG_RESTORE)
        return reg_restore(argc, argvW);

    if (!parse_registry_key(argvW[2], &root, &path, &key_name))
        return 1;

    for (i = 3; i < argc; i++)
    {
        if (argvW[i][0] == '/' || argvW[i][0] == '-')
        {
            WCHAR *ptr = &argvW[i][1];

            if (!lstrcmpiW(ptr, switchVEW))
            {
                value_empty = TRUE;
                continue;
            }
            else if (!lstrcmpiW(ptr, switchVAW))
            {
                value_all = TRUE;
                continue;
            }
            else if (!ptr[0] || ptr[1])
            {
                output_message(STRING_INVALID_CMDLINE);
                return 1;
            }

            switch(tolowerW(argvW[i][1]))
            {
            case 'v':
                if (value_name || !(value_name = argvW[++i]))
                {
                    output_message(STRING_INVALID_CMDLINE);
                    return 1;
                }
                break;
            case 't':
                if (type || !(type = argvW[++i]))
                {
                    output_message(STRING_INVALID_CMDLINE);
                    return 1;
                }
                break;
            case 'd':
                if (data || !(data = argvW[++i]))
                {
                    output_message(STRING_INVALID_CMDLINE);
                    return 1;
                }
                break;
            case 's':
                if (op == REG_QUERY)
                {
                    recurse = TRUE;
                    break;
                }

                ptr = argvW[++i];
                if (!ptr || strlenW(ptr) != 1)
                {
                    output_message(STRING_INVALID_CMDLINE);
                    return 1;
                }
                separator = ptr[0];
                break;
            case 'f':
                force = TRUE;
                break;
            default:
                output_message(STRING_INVALID_CMDLINE);
                return 1;
            }
        }
    }

    if ((value_name && value_empty) || (value_name && value_all) || (value_empty && value_all))
    {
        output_message(STRING_INVALID_CMDLINE);
        return 1;
    }

    if (op == REG_ADD)
        ret = reg_add(root, path, value_name, value_empty, type, separator, data, force);
    else if (op == REG_DELETE)
        ret = reg_delete(root, path, key_name, value_name, value_empty, value_all, force);
    else
        ret = reg_query(root, path, key_name, value_name, value_empty, recurse);
    return ret;
}