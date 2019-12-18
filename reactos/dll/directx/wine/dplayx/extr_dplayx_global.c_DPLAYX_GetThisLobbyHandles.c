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
struct TYPE_3__ {scalar_t__ hInformOnAppStart; scalar_t__ hInformOnAppDeath; scalar_t__ hInformOnSettingRead; } ;
typedef  scalar_t__* LPHANDLE ;
typedef  TYPE_1__* LPDPLAYX_LOBBYDATA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_IsAppIdLobbied (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL DPLAYX_GetThisLobbyHandles( LPHANDLE lphStart,
                                        LPHANDLE lphDeath,
                                        LPHANDLE lphConnRead,
                                        BOOL     bClearSetHandles )
{
  LPDPLAYX_LOBBYDATA lpLData;

  DPLAYX_AcquireSemaphore();

  if( !DPLAYX_IsAppIdLobbied( 0, &lpLData ) )
  {
    DPLAYX_ReleaseSemaphore();
    return FALSE;
  }

  if( lphStart != NULL )
  {
    if( lpLData->hInformOnAppStart == 0 )
    {
      DPLAYX_ReleaseSemaphore();
      return FALSE;
    }

    *lphStart = lpLData->hInformOnAppStart;

    if( bClearSetHandles )
    {
      CloseHandle( lpLData->hInformOnAppStart );
      lpLData->hInformOnAppStart = 0;
    }
  }

  if( lphDeath != NULL )
  {
    if( lpLData->hInformOnAppDeath == 0 )
    {
      DPLAYX_ReleaseSemaphore();
      return FALSE;
    }

    *lphDeath = lpLData->hInformOnAppDeath;

    if( bClearSetHandles )
    {
      CloseHandle( lpLData->hInformOnAppDeath );
      lpLData->hInformOnAppDeath = 0;
    }
  }

  if( lphConnRead != NULL )
  {
    if( lpLData->hInformOnSettingRead == 0 )
    {
      DPLAYX_ReleaseSemaphore();
      return FALSE;
    }

    *lphConnRead = lpLData->hInformOnSettingRead;

    if( bClearSetHandles )
    {
      CloseHandle( lpLData->hInformOnSettingRead );
      lpLData->hInformOnSettingRead = 0;
    }
  }

  DPLAYX_ReleaseSemaphore();

  return TRUE;
}