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
typedef  scalar_t__ const* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  copy_escape (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__ need_escape (scalar_t__ const) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__ const*) ; 
 scalar_t__* strrchrW (scalar_t__ const*,char) ; 

__attribute__((used)) static WCHAR *escape_url( LPCWSTR url, DWORD *len )
{
    WCHAR *ret;
    const WCHAR *p, *q;

    if ((p = q = strrchrW( url, '/' )))
    {
        while (*q)
        {
            if (need_escape( *q )) *len += 2;
            q++;
        }
    }
    if (!(ret = heap_alloc( (*len + 1) * sizeof(WCHAR) ))) return NULL;
    if (!p) strcpyW( ret, url );
    else
    {
        memcpy( ret, url, (p - url) * sizeof(WCHAR) );
        copy_escape( ret + (p - url), p, q - p );
    }
    return ret;
}