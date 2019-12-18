#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_2__ {scalar_t__ dwAppID; scalar_t__ hInformOnSettingRead; scalar_t__ hInformOnAppDeath; scalar_t__ hInformOnAppStart; int /*<<< orphan*/  dwAppLaunchedFromID; } ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPLAYX_AcquireSemaphore () ; 
 int /*<<< orphan*/  DPLAYX_ReleaseSemaphore () ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  TRACE (char*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* lobbyData ; 
 size_t numSupportedLobbies ; 

BOOL DPLAYX_CreateLobbyApplication( DWORD dwAppID )
{
  UINT i;

  /* 0 is the marker for unused application data slots */
  if( dwAppID == 0 )
  {
    return FALSE;
  }

  DPLAYX_AcquireSemaphore();

  /* Find an empty space in the list and insert the data */
  for( i=0; i < numSupportedLobbies; i++ )
  {
    if( lobbyData[ i ].dwAppID == 0 )
    {
      /* This process is now lobbied */
      TRACE( "Setting lobbyData[%u] for (0x%08x,0x%08x)\n",
              i, dwAppID, GetCurrentProcessId() );

      lobbyData[ i ].dwAppID              = dwAppID;
      lobbyData[ i ].dwAppLaunchedFromID  = GetCurrentProcessId();

      /* FIXME: Where is the best place for this? In interface or here? */
      lobbyData[ i ].hInformOnAppStart = 0;
      lobbyData[ i ].hInformOnAppDeath = 0;
      lobbyData[ i ].hInformOnSettingRead = 0;

      DPLAYX_ReleaseSemaphore();
      return TRUE;
    }
  }

  ERR( "No empty lobbies\n" );

  DPLAYX_ReleaseSemaphore();
  return FALSE;
}