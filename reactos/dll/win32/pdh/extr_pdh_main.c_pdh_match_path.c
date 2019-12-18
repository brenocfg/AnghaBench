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
typedef  char* LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ is_local_machine (char*,int) ; 
 char* strchrW (char*,char) ; 
 int /*<<< orphan*/  strcmpW (char const*,char*) ; 
 char* strrchrW (char*,char) ; 

__attribute__((used)) static BOOL pdh_match_path( LPCWSTR fullpath, LPCWSTR path )
{
    const WCHAR *p;

    if (path[0] == '\\' && path[1] == '\\' && (p = strchrW( path + 2, '\\' )) &&
        is_local_machine( path + 2, p - path - 2 ))
    {
        path += p - path;
    }
    if (strchrW( path, '\\' )) p = fullpath;
    else p = strrchrW( fullpath, '\\' ) + 1;
    return !strcmpW( p, path );
}