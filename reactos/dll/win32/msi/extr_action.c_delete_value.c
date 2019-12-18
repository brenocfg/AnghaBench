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
typedef  int /*<<< orphan*/  MSICOMPONENT ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KEY_QUERY_VALUE ; 
 int KEY_SET_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteValueW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  delete_key (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  open_key (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void delete_value( const MSICOMPONENT *comp, HKEY root, const WCHAR *path, const WCHAR *value )
{
    LONG res;
    HKEY hkey;
    DWORD num_subkeys, num_values;

    if ((hkey = open_key( comp, root, path, FALSE, KEY_SET_VALUE | KEY_QUERY_VALUE )))
    {
        if ((res = RegDeleteValueW( hkey, value )))
            TRACE("failed to delete value %s (%d)\n", debugstr_w(value), res);

        res = RegQueryInfoKeyW( hkey, NULL, NULL, NULL, &num_subkeys, NULL, NULL, &num_values,
                                NULL, NULL, NULL, NULL );
        RegCloseKey( hkey );
        if (!res && !num_subkeys && !num_values)
        {
            TRACE("removing empty key %s\n", debugstr_w(path));
            delete_key( comp, root, path );
        }
    }
}