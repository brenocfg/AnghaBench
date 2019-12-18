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
typedef  int /*<<< orphan*/  request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__* LPDWORD ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ auth_scheme_from_header (int /*<<< orphan*/ *) ; 
 scalar_t__ get_last_error () ; 
 int /*<<< orphan*/ * heap_alloc (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_headers (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static BOOL query_auth_schemes( request_t *request, DWORD level, LPDWORD supported, LPDWORD first )
{
    DWORD index = 0, supported_schemes = 0, first_scheme = 0;
    BOOL ret = FALSE;

    for (;;)
    {
        WCHAR *buffer;
        DWORD size, scheme;

        size = 0;
        query_headers( request, level, NULL, NULL, &size, &index );
        if (get_last_error() != ERROR_INSUFFICIENT_BUFFER) break;

        index--;
        if (!(buffer = heap_alloc( size ))) return FALSE;
        if (!query_headers( request, level, NULL, buffer, &size, &index ))
        {
            heap_free( buffer );
            return FALSE;
        }
        scheme = auth_scheme_from_header( buffer );
        heap_free( buffer );
        if (!scheme) continue;

        if (!first_scheme) first_scheme = scheme;
        supported_schemes |= scheme;

        ret = TRUE;
    }

    if (ret)
    {
        *supported = supported_schemes;
        *first = first_scheme;
    }
    return ret;
}