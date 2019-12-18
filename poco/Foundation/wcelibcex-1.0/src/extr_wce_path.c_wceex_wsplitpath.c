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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 size_t _MAX_DIR ; 
 int _MAX_EXT ; 
 int _MAX_FNAME ; 
 int /*<<< orphan*/  wcsncat (scalar_t__*,scalar_t__ const*,int) ; 
 scalar_t__* wcsrchr (scalar_t__ const*,char) ; 

void wceex_wsplitpath( const wchar_t *path, 
                       wchar_t *drive, wchar_t *dir, wchar_t *name, wchar_t *ext )
{
    wchar_t *slash, *bslash;
    if( drive )
        *drive = 0;
    if( dir )
        *dir = 0;
    if( name )
        *name = 0;
    if( ext )
        *ext = 0;
    if( !path || *path == 0 )
        return;
    slash = wcsrchr( path, '/' );
    bslash = wcsrchr( path, '\\' );
    if( slash > bslash )
        bslash = slash;
    if( bslash )
    {
        if( dir )
        {
            size_t count = (bslash - path) / sizeof(wchar_t);
            if( count >= _MAX_DIR )
                count = _MAX_DIR - 1;
            wcsncat( dir, path, count );
        }
        bslash++;
    }
    else
        bslash = (wchar_t*)path;
    if( name )
    {
        wchar_t* dot;
        wcsncat( name, bslash, _MAX_FNAME - 1 );
        dot = wcsrchr( name, '.' );
        if( dot )
            *dot = 0;
    }
    if( ext )
    {
        wchar_t* dot = wcsrchr( bslash, '.' );
        if( dot )
            wcsncat( ext, dot, _MAX_EXT - 1 );
    }
}