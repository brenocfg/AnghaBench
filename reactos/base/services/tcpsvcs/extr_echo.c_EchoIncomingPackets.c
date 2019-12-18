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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RECV_BUF ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  bShutdown ; 
 scalar_t__ recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static BOOL
EchoIncomingPackets(SOCKET sock)
{
    CHAR readBuffer[RECV_BUF];
    WCHAR logBuf[256];
    INT totalSentBytes;
    INT readBytes;
    INT retVal;

    do 
    {
        readBytes = recv(sock, readBuffer, RECV_BUF, 0);
        if (readBytes > 0)
        {
            swprintf(logBuf, L"Received %d bytes from client", readBytes);
            LogEvent(logBuf, 0, 0, LOG_FILE);

            totalSentBytes = 0;
            while (!bShutdown && totalSentBytes < readBytes)
            {
                retVal = send(sock, readBuffer + totalSentBytes, readBytes - totalSentBytes, 0);
                if (retVal > 0)
                {
                    swprintf(logBuf, L"Sent %d bytes back to client", retVal);
                    LogEvent(logBuf, 0, 0, LOG_FILE);
                    totalSentBytes += retVal;
                }
                else if (retVal == SOCKET_ERROR)
                {
                    LogEvent(L"Echo: socket error", WSAGetLastError(), 0, LOG_ERROR);
                    return FALSE;
                }
                else
                {
                    /* Client closed connection before we could reply to
                       all the data it sent, so quit early. */
                    LogEvent(L"Peer unexpectedly dropped connection!", 0, 0, LOG_FILE);
                    return FALSE;
                }
            }
        }
        else if (readBytes == SOCKET_ERROR)
        {
            LogEvent(L"Echo: socket error", WSAGetLastError(), 0, LOG_ERROR);
            return FALSE;
        }
    } while ((readBytes != 0) && (!bShutdown));

    if (!bShutdown)
        LogEvent(L"Echo: Connection closed by peer", 0, 0, LOG_FILE);

    return TRUE;
}