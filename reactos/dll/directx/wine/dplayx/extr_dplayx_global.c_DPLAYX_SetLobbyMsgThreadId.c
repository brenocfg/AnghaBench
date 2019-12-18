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
struct TYPE_3__ {int /*<<< orphan*/  dwLobbyMsgThreadId; } ;
typedef  TYPE_1__* LPDPLAYX_LOBBYDATA ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_IsAppIdLobbied (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL DPLAYX_SetLobbyMsgThreadId( DWORD dwAppId, DWORD dwThreadId )
{
  LPDPLAYX_LOBBYDATA lpLobbyData;

  DPLAYX_AcquireSemaphore();

  if( !DPLAYX_IsAppIdLobbied( dwAppId, &lpLobbyData ) )
  {
    DPLAYX_ReleaseSemaphore();
    return FALSE;
  }

  lpLobbyData->dwLobbyMsgThreadId = dwThreadId;

  DPLAYX_ReleaseSemaphore();

  return TRUE;
}