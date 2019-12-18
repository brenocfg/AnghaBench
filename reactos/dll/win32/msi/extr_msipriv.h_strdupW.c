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
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 

__attribute__((used)) static inline LPWSTR strdupW( LPCWSTR src )
{
    LPWSTR dest;
    if (!src) return NULL;
    dest = msi_alloc( (lstrlenW(src)+1)*sizeof(WCHAR) );
    if (dest)
        lstrcpyW(dest, src);
    return dest;
}