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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *append_path( const WCHAR *path, const WCHAR *segment, UINT *len )
{
    UINT len_path = 0, len_segment = strlenW( segment );
    WCHAR *ret;

    *len = 0;
    if (path) len_path = strlenW( path );
    if (!(ret = heap_alloc( (len_path + len_segment + 2) * sizeof(WCHAR) ))) return NULL;
    if (path && len_path)
    {
        memcpy( ret, path, len_path * sizeof(WCHAR) );
        ret[len_path] = '\\';
        *len += len_path + 1;
    }
    memcpy( ret + *len, segment, len_segment * sizeof(WCHAR) );
    *len += len_segment;
    ret[*len] = 0;
    return ret;
}