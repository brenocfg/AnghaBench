#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; } ;
struct TYPE_6__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  char* LPWSTR ;
typedef  int LONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateProcessW (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DETACHED_PROCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetSystemDirectoryW (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wow64DisableWow64FsRedirection (void**) ; 
 int /*<<< orphan*/  Wow64RevertWow64FsRedirection (void*) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL run_winemenubuilder( const WCHAR *args )
{
    static const WCHAR menubuilder[] = {'\\','w','i','n','e','m','e','n','u','b','u','i','l','d','e','r','.','e','x','e',0};
    LONG len;
    LPWSTR buffer;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    BOOL ret;
    WCHAR app[MAX_PATH];
    void *redir;

    GetSystemDirectoryW( app, MAX_PATH - ARRAY_SIZE( menubuilder ));
    lstrcatW( app, menubuilder );

    len = (lstrlenW( app ) + lstrlenW( args ) + 1) * sizeof(WCHAR);
    buffer = heap_alloc( len );
    if( !buffer )
        return FALSE;

    lstrcpyW( buffer, app );
    lstrcatW( buffer, args );

    TRACE("starting %s\n",debugstr_w(buffer));

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);

    Wow64DisableWow64FsRedirection( &redir );
    ret = CreateProcessW( app, buffer, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &si, &pi );
    Wow64RevertWow64FsRedirection( redir );

    heap_free( buffer );

    if (ret)
    {
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
    }

    return ret;
}