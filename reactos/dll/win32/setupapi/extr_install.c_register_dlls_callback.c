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
struct register_dll_info {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int MAX_INF_STRING_LENGTH ; 
 char* PARSER_get_dest_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetIntField (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ SetupGetStringFieldW (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ do_register_dll (struct register_dll_info*,char*,int,int,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL register_dlls_callback( HINF hinf, PCWSTR field, void *arg )
{
    struct register_dll_info *info = arg;
    INFCONTEXT context;
    BOOL ret = TRUE;
    BOOL ok = SetupFindFirstLineW( hinf, field, NULL, &context );

    for (; ok; ok = SetupFindNextLine( &context, &context ))
    {
        WCHAR *path, *args, *p;
        WCHAR buffer[MAX_INF_STRING_LENGTH];
        INT flags, timeout;

        /* get directory */
        if (!(path = PARSER_get_dest_dir( &context ))) continue;

        /* get dll name */
        if (!SetupGetStringFieldW( &context, 3, buffer, sizeof(buffer)/sizeof(WCHAR), NULL ))
            goto done;
        if (!(p = HeapReAlloc( GetProcessHeap(), 0, path,
                               (strlenW(path) + strlenW(buffer) + 2) * sizeof(WCHAR) ))) goto done;
        path = p;
        p += strlenW(p);
        if (p == path || p[-1] != '\\') *p++ = '\\';
        strcpyW( p, buffer );

        /* get flags */
        if (!SetupGetIntField( &context, 4, &flags )) flags = 0;

        /* get timeout */
        if (!SetupGetIntField( &context, 5, &timeout )) timeout = 60;

        /* get command line */
        args = NULL;
        if (SetupGetStringFieldW( &context, 6, buffer, sizeof(buffer)/sizeof(WCHAR), NULL ))
            args = buffer;

        ret = do_register_dll( info, path, flags, timeout, args );

    done:
        HeapFree( GetProcessHeap(), 0, path );
        if (!ret) break;
    }
    return ret;
}