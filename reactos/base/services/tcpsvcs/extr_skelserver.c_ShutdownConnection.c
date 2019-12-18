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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BUF ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_SEND ; 
 scalar_t__ SOCKET_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (char*,char*,scalar_t__) ; 

BOOL
ShutdownConnection(SOCKET sock,
                   BOOL bRec)
{
    WCHAR logBuf[256];

    /* Disallow any further data sends.  This will tell the other side
       that we want to go away now.  If we skip this step, we don't
       shut the connection down nicely. */
    if (shutdown(sock, SD_SEND) == SOCKET_ERROR)
    {
        LogEvent(L"Error in shutdown()", WSAGetLastError(), 0, LOG_ERROR);
        return FALSE;
    }

      /* Receive any extra data still sitting on the socket
         before we close it */
    if (bRec)
    {
        CHAR readBuffer[BUF];
        INT ret;

        do
        {
            ret = recv(sock, readBuffer, BUF, 0);
            if (ret >= 0)
            {
                swprintf(logBuf, L"FYI, received %d unexpected bytes during shutdown", ret);
                LogEvent(logBuf, 0, 0, LOG_FILE);
            }
        } while (ret > 0);
    }

    closesocket(sock);

    return TRUE;
}