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
typedef  int /*<<< orphan*/  static_buffer ;
typedef  int /*<<< orphan*/  (* iterate_fields_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextMatchLineW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupGetFieldCount (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_field_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static BOOL iterate_section_fields( HINF hinf, PCWSTR section, PCWSTR key,
                                    iterate_fields_func callback, void *arg )
{
    WCHAR static_buffer[200];
    WCHAR *buffer = static_buffer;
    DWORD size = sizeof(static_buffer)/sizeof(WCHAR);
    INFCONTEXT context;
    BOOL ret = FALSE;

    BOOL ok = SetupFindFirstLineW( hinf, section, key, &context );
    while (ok)
    {
        UINT i, count = SetupGetFieldCount( &context );
        for (i = 1; i <= count; i++)
        {
            if (!(buffer = get_field_string( &context, i, buffer, static_buffer, &size )))
                goto done;
            if (!callback( hinf, buffer, arg ))
            {
                WARN("callback failed for %s %s err %d\n",
                     debugstr_w(section), debugstr_w(buffer), GetLastError() );
                goto done;
            }
        }
        ok = SetupFindNextMatchLineW( &context, key, &context );
    }
    ret = TRUE;
 done:
    if (buffer != static_buffer) HeapFree( GetProcessHeap(), 0, buffer );
    return ret;
}