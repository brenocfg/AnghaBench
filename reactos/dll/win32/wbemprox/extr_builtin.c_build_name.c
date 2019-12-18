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
typedef  int UINT ;

/* Variables and functions */
 char* heap_alloc (int) ; 

__attribute__((used)) static WCHAR *build_name( WCHAR drive, const WCHAR *path )
{
    UINT i = 0, len = 0;
    const WCHAR *p;
    WCHAR *ret;

    for (p = path; *p; p++)
    {
        if (*p == '\\') len += 2;
        else len++;
    };
    if (!(ret = heap_alloc( (len + 5) * sizeof(WCHAR) ))) return NULL;
    ret[i++] = drive;
    ret[i++] = ':';
    ret[i++] = '\\';
    ret[i++] = '\\';
    for (p = path; *p; p++)
    {
        if (*p != '\\') ret[i++] = *p;
        else
        {
            ret[i++] = '\\';
            ret[i++] = '\\';
        }
    }
    ret[i] = 0;
    return ret;
}