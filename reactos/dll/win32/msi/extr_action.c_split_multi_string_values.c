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
typedef  int /*<<< orphan*/ **** WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ ******** msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ******) ; 
 int /*<<< orphan*/ ******* strdupW (int /*<<< orphan*/ **** const*) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ **** const*) ; 

__attribute__((used)) static WCHAR **split_multi_string_values( const WCHAR *str, DWORD len, DWORD *count )
{
    const WCHAR *p = str;
    WCHAR **ret;
    int i = 0;

    *count = 0;
    if (!str) return NULL;
    while ((p - str) < len)
    {
        p += strlenW( p ) + 1;
        (*count)++;
    }
    if (!(ret = msi_alloc( *count * sizeof(WCHAR *) ))) return NULL;
    p = str;
    while ((p - str) < len)
    {
        if (!(ret[i] = strdupW( p )))
        {
            for (; i >= 0; i--) msi_free( ret[i] );
            msi_free( ret );
            return NULL;
        }
        p += strlenW( p ) + 1;
        i++;
    }
    return ret;
}