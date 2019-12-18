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
struct TYPE_3__ {void* hInformOnSettingRead; void* hInformOnAppDeath; void* hInformOnAppStart; } ;
typedef  TYPE_1__* LPDPLAYX_LOBBYDATA ;
typedef  void* HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_IsAppIdLobbied (scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL DPLAYX_SetLobbyHandles( DWORD dwAppID,
                             HANDLE hStart, HANDLE hDeath, HANDLE hConnRead )
{
  LPDPLAYX_LOBBYDATA lpLData;

  /* Need to explicitly give lobby application. Can't set for yourself */
  if( dwAppID == 0 )
  {
    return FALSE;
  }

  DPLAYX_AcquireSemaphore();

  if( !DPLAYX_IsAppIdLobbied( dwAppID, &lpLData ) )
  {
    DPLAYX_ReleaseSemaphore();
    return FALSE;
  }

  lpLData->hInformOnAppStart    = hStart;
  lpLData->hInformOnAppDeath    = hDeath;
  lpLData->hInformOnSettingRead = hConnRead;

  DPLAYX_ReleaseSemaphore();

  return TRUE;
}