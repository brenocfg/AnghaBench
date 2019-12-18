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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STRING_INVALID_SYSTEM_KEY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* get_long_key (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  output_message (int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  path_get_rootkey (scalar_t__ const*) ; 
 int /*<<< orphan*/  sane_path (scalar_t__ const*) ; 
 scalar_t__* strchrW (scalar_t__ const*,char) ; 

BOOL parse_registry_key(const WCHAR *key, HKEY *root, WCHAR **path, WCHAR **long_key)
{
    if (!sane_path(key))
        return FALSE;

    *path = strchrW(key, '\\');
    if (*path) (*path)++;

    *root = path_get_rootkey(key);
    if (!*root)
    {
        if (*path) *(*path - 1) = 0;
        output_message(STRING_INVALID_SYSTEM_KEY, key);
        return FALSE;
    }

    *long_key = get_long_key(*root, *path);

    return TRUE;
}