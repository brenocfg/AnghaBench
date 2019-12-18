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
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * CharLowerW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * strstrW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *strstriW( const WCHAR *str, const WCHAR *sub )
{
    LPWSTR strlower, sublower, r;
    strlower = CharLowerW( strdupW( str ) );
    sublower = CharLowerW( strdupW( sub ) );
    r = strstrW( strlower, sublower );
    if (r)
        r = (LPWSTR)str + (r - strlower);
    msi_free( strlower );
    msi_free( sublower );
    return r;
}