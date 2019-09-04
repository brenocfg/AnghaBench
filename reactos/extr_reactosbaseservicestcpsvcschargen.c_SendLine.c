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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LINESIZE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
SendLine(SOCKET sock, LPSTR lpLine)
{
    BOOL bRet = FALSE;

    /*FIXME: need to establish if peer closes connection, not just report a socket error */
    INT retVal = send(sock, lpLine, LINESIZE, 0);
    if (retVal > 0)
    {
        if (retVal == LINESIZE)
        {
            bRet = TRUE;
        }
        else
        {
            LogEvent(L"Chargen: Not sent enough bytes", 0, 0, LOG_FILE);
        }
    }
    else if (retVal == SOCKET_ERROR)
    {
        LogEvent(L"Chargen: Socket error\n", WSAGetLastError(), 0, LOG_ERROR);
    }
    else
    {
        LogEvent(L"Chargen: unknown error\n", WSAGetLastError(), 0, LOG_ERROR);
    }

    return bRet;
}