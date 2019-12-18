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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msi_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE *reg_get_value( HKEY hkey, const WCHAR *name, DWORD *type, DWORD *size )
{
    BYTE *ret;
    if (RegQueryValueExW( hkey, name, NULL, NULL, NULL, size )) return NULL;
    if (!(ret = msi_alloc( *size ))) return NULL;
    RegQueryValueExW( hkey, name, NULL, type, ret, size );
    return ret;
}