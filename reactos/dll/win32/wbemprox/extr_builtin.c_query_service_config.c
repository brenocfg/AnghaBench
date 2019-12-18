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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  QUERY_SERVICE_CONFIGW ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  OpenServiceW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ QueryServiceConfigW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVICE_QUERY_CONFIG ; 
 int /*<<< orphan*/ * heap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static QUERY_SERVICE_CONFIGW *query_service_config( SC_HANDLE manager, const WCHAR *name )
{
    QUERY_SERVICE_CONFIGW *config = NULL;
    SC_HANDLE service;
    DWORD size;

    if (!(service = OpenServiceW( manager, name, SERVICE_QUERY_CONFIG ))) return NULL;
    QueryServiceConfigW( service, NULL, 0, &size );
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) goto done;
    if (!(config = heap_alloc( size ))) goto done;
    if (QueryServiceConfigW( service, config, size, &size )) goto done;
    heap_free( config );
    config = NULL;

done:
    CloseServiceHandle( service );
    return config;
}