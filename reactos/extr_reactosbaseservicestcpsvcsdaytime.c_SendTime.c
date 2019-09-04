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
typedef  int /*<<< orphan*/  SOCKET ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
SendTime(SOCKET sock, CHAR *time)
{
    SIZE_T stringSize = strlen(time) + 1;
    if (send(sock, time, stringSize, 0) == SOCKET_ERROR)
    {
        LogEvent(L"DayTime: Error sending data", WSAGetLastError(), 0, LOG_ERROR);
        return FALSE;
    }

    return TRUE;
}