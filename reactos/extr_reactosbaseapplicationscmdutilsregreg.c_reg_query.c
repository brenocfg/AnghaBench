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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRING_CANNOT_FIND ; 
 int /*<<< orphan*/  STRING_MATCHES_FOUND ; 
 int /*<<< orphan*/  newlineW ; 
 int /*<<< orphan*/  num_values_found ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  output_string (int /*<<< orphan*/ ) ; 
 int query_all (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int query_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int reg_query(HKEY root, WCHAR *path, WCHAR *key_name, WCHAR *value_name,
                     BOOL value_empty, BOOL recurse)
{
    HKEY key;
    int ret;

    if (RegOpenKeyExW(root, path, 0, KEY_READ, &key) != ERROR_SUCCESS)
    {
        output_message(STRING_CANNOT_FIND);
        return 1;
    }

    output_string(newlineW);

    if (value_name || value_empty)
    {
        ret = query_value(key, value_name, key_name, recurse);
        if (recurse)
            output_message(STRING_MATCHES_FOUND, num_values_found);
    }
    else
        ret = query_all(key, key_name, recurse);

    RegCloseKey(key);

    return ret;
}