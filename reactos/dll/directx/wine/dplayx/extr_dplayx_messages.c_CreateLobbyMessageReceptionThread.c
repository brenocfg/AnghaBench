#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * hSettingRead; int /*<<< orphan*/ * hDeath; int /*<<< orphan*/ * hStart; int /*<<< orphan*/  hNotifyEvent; } ;
typedef  TYPE_1__* LPMSGTHREADINFO ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPL_MSG_ThreadMain ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

DWORD CreateLobbyMessageReceptionThread( HANDLE hNotifyEvent, HANDLE hStart,
                                         HANDLE hDeath, HANDLE hConnRead )
{
  DWORD           dwMsgThreadId;
  LPMSGTHREADINFO lpThreadInfo;
  HANDLE          hThread;

  lpThreadInfo = HeapAlloc( GetProcessHeap(), 0, sizeof( *lpThreadInfo ) );
  if( lpThreadInfo == NULL )
  {
    return 0;
  }

  /* The notify event may or may not exist. Depends if async comm or not */
  if( hNotifyEvent &&
      !DuplicateHandle( GetCurrentProcess(), hNotifyEvent,
                        GetCurrentProcess(), &lpThreadInfo->hNotifyEvent,
                        0, FALSE, DUPLICATE_SAME_ACCESS ) )
  {
    ERR( "Unable to duplicate event handle\n" );
    goto error;
  }

  /* These 3 handles don't need to be duplicated because we don't keep a
   * reference to them where they're created. They're created specifically
   * for the message thread
   */
  lpThreadInfo->hStart       = hStart;
  lpThreadInfo->hDeath       = hDeath;
  lpThreadInfo->hSettingRead = hConnRead;

  hThread = CreateThread( NULL,                  /* Security attribs */
                          0,                     /* Stack */
                          DPL_MSG_ThreadMain,    /* Msg reception function */
                          lpThreadInfo,          /* Msg reception func parameter */
                          0,                     /* Flags */
                          &dwMsgThreadId         /* Updated with thread id */
                        );
  if ( hThread == NULL )
  {
    ERR( "Unable to create msg thread\n" );
    goto error;
  }

  CloseHandle(hThread);

  return dwMsgThreadId;

error:

  HeapFree( GetProcessHeap(), 0, lpThreadInfo );

  return 0;
}