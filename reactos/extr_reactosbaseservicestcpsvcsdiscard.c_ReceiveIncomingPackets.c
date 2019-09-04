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
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  bShutdown ; 
 scalar_t__ recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static BOOL
ReceiveIncomingPackets(SOCKET sock)
{
    CHAR readBuffer[BUFSIZE];
    INT readBytes;

    do
    {
        readBytes = recv(sock, readBuffer, BUFSIZE, 0);
        if (readBytes > 0)
        {
            TCHAR logBuf[256];

            swprintf(logBuf, L"Discard: Received %d bytes from client", readBytes);
            LogEvent(logBuf, 0, 0, LOG_FILE);
        }
        else if (readBytes == SOCKET_ERROR)
        {
            LogEvent(L"Discard: Socket Error", WSAGetLastError(), 0, LOG_ERROR);
            return FALSE;
        }
    } while ((readBytes > 0) && (!bShutdown));

    if (!bShutdown)
        LogEvent(L"Discard: Connection closed by peer", 0, 0, LOG_FILE);

    return TRUE;
}