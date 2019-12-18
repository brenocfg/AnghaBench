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
typedef  char wchar_t ;

/* Variables and functions */
 int _MAX_PATH ; 
 char* wcschr (char*,char) ; 
 size_t wcslen (char*) ; 
 int /*<<< orphan*/  wcsncat (char*,char const*,size_t) ; 

void wceex_wmakepath( wchar_t *path,
                      const wchar_t *drive, const wchar_t *dir,
                      const wchar_t *name, const wchar_t *ext )
{
    wchar_t* ptr = path;
    size_t slen, sbuf = _MAX_PATH - 1;
    *path = 0;
    if( drive && *drive )
    {
        wcsncat( ptr, drive, sbuf );
        slen = wcslen( ptr );
        ptr += slen;
        sbuf -= slen;
    }
    if( dir && *dir && sbuf )
    {
        wcsncat( ptr, dir, sbuf );
        slen = wcslen( ptr );
        ptr += slen - 1;
        sbuf -= slen;
        // backslash ?
        if( sbuf && *ptr != '\\' && *ptr != '/' )
        {
            wchar_t* slash = wcschr( path, '/' );
            if( !slash )
                slash = wcschr( path, '\\' );
            ptr++;
            if( slash )
                *ptr = *slash;
            else
                *ptr = '\\';
            ptr++;
            *ptr = 0;
            sbuf--;
        }
        ptr++;
    }
    if( name && *name && sbuf )
    {
        wcsncat( ptr, name, sbuf );
        slen = wcslen( ptr );
        ptr += slen;
        sbuf -= slen;
    }
    if( ext && *ext && sbuf )
    {
        if( *ext != '.' )
        {
            *ptr = '.';
            ptr++;
            *ptr = 0;
            sbuf--;
        }
        if( sbuf )
            wcsncat( ptr, ext, sbuf );
    }
}