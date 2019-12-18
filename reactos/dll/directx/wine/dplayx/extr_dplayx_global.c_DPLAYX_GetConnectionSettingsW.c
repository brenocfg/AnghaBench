#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lpConn; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__* LPDWORD ;
typedef  TYPE_1__* LPDPLAYX_LOBBYDATA ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPERR_BUFFERTOOSMALL ; 
 int /*<<< orphan*/  DPERR_NOTLOBBIED ; 
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_CopyConnStructW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DPLAYX_GetThisLobbyHandles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPLAYX_IsAppIdLobbied (scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 scalar_t__ DPLAYX_SizeOfLobbyDataW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  TRUE ; 

HRESULT DPLAYX_GetConnectionSettingsW
( DWORD dwAppID,
  LPVOID lpData,
  LPDWORD lpdwDataSize )
{
  LPDPLAYX_LOBBYDATA lpDplData;
  DWORD              dwRequiredDataSize = 0;
  HANDLE             hInformOnSettingRead;

  DPLAYX_AcquireSemaphore();

  if ( ! DPLAYX_IsAppIdLobbied( dwAppID, &lpDplData ) )
  {
    DPLAYX_ReleaseSemaphore();
    return DPERR_NOTLOBBIED;
  }

  dwRequiredDataSize = DPLAYX_SizeOfLobbyDataW( lpDplData->lpConn );

  /* Do they want to know the required buffer size or is the provided buffer
   * big enough?
   */
  if ( ( lpData == NULL ) ||
       ( *lpdwDataSize < dwRequiredDataSize )
     )
  {
    DPLAYX_ReleaseSemaphore();

    *lpdwDataSize = DPLAYX_SizeOfLobbyDataW( lpDplData->lpConn );

    return DPERR_BUFFERTOOSMALL;
  }

  DPLAYX_CopyConnStructW( lpData, lpDplData->lpConn );

  DPLAYX_ReleaseSemaphore();

  /* They have gotten the information - signal the event if required */
  if( DPLAYX_GetThisLobbyHandles( NULL, NULL, &hInformOnSettingRead, FALSE ) &&
      hInformOnSettingRead
    )
  {
    BOOL bSuccess;
    bSuccess = SetEvent( hInformOnSettingRead );
    TRACE( "Signalling setting read event %p %s\n",
             hInformOnSettingRead, bSuccess ? "succeed" : "failed" );

    /* Close out handle */
    DPLAYX_GetThisLobbyHandles( NULL, NULL, &hInformOnSettingRead, TRUE );
  }

  return DP_OK;
}