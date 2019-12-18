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
typedef  int /*<<< orphan*/  szFormat ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LPCOLESTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  run_winemenubuilder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static BOOL StartLinkProcessor( LPCOLESTR szLink )
{
    static const WCHAR szFormat[] = { ' ','-','w',' ','-','u',' ','"','%','s','"',0 };
    LONG len;
    LPWSTR buffer;
    BOOL ret;

    len = sizeof(szFormat) + lstrlenW( szLink ) * sizeof(WCHAR);
    buffer = heap_alloc( len );
    if( !buffer )
        return FALSE;

    swprintf( buffer, szFormat, szLink );
    ret = run_winemenubuilder( buffer );
    heap_free( buffer );
    return ret;
}