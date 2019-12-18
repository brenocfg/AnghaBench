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

/* Variables and functions */
 size_t _MAX_DIR ; 
 int _MAX_EXT ; 
 int _MAX_FNAME ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

void wceex_splitpath( const char *path, 
                      char *drive, char *dir, char *name, char *ext )
{
    char *slash, *bslash;
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
    slash = strrchr( path, '/' );
    bslash = strrchr( path, '\\' );
    if( slash > bslash )
        bslash = slash;
    if( bslash )
    {
        if( dir )
        {
            size_t count = (bslash - path);
            if( count >= _MAX_DIR )
                count = _MAX_DIR - 1;
            strncat( dir, path, count );
        }
        bslash++;
    }
    else
        bslash = (char*)path;
    if( name )
    {
        char* dot;
        strncat( name, bslash, _MAX_FNAME - 1 );
        dot = strrchr( name, '.' );
        if( dot )
            *dot = 0;
    }
    if( ext )
    {
        char* dot = strrchr( bslash, '.' );
        if( dot )
            strncat( ext, dot, _MAX_EXT - 1 );
    }
}