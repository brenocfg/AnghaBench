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
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DH_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKey (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegQueryValueEx (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

PCHAR RegReadString( HKEY Root, PCHAR Subkey, PCHAR Value ) {
    PCHAR SubOut = NULL;
    DWORD SubOutLen = 0, Error = 0;
    HKEY  ValueKey = NULL;

    DH_DbgPrint(MID_TRACE,("Looking in %x:%s:%s\n", Root, Subkey, Value ));

    if( Subkey && strlen(Subkey) ) {
        if( RegOpenKey( Root, Subkey, &ValueKey ) != ERROR_SUCCESS )
            goto regerror;
    } else ValueKey = Root;

    DH_DbgPrint(MID_TRACE,("Got Key %x\n", ValueKey));

    if( (Error = RegQueryValueEx( ValueKey, Value, NULL, NULL,
                                  (LPBYTE)SubOut, &SubOutLen )) != ERROR_SUCCESS )
        goto regerror;

    DH_DbgPrint(MID_TRACE,("Value %s has size %d\n", Value, SubOutLen));

    if( !(SubOut = (CHAR*) malloc(SubOutLen)) )
        goto regerror;

    if( (Error = RegQueryValueEx( ValueKey, Value, NULL, NULL,
                                  (LPBYTE)SubOut, &SubOutLen )) != ERROR_SUCCESS )
        goto regerror;

    DH_DbgPrint(MID_TRACE,("Value %s is %s\n", Value, SubOut));

    goto cleanup;

regerror:
    if( SubOut ) { free( SubOut ); SubOut = NULL; }
cleanup:
    if( ValueKey && ValueKey != Root ) {
        DH_DbgPrint(MID_TRACE,("Closing key %x\n", ValueKey));
        RegCloseKey( ValueKey );
    }

    DH_DbgPrint(MID_TRACE,("Returning %x with error %d\n", SubOut, Error));

    return SubOut;
}