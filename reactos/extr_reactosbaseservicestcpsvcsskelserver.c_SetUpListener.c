#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_2__ SOCKADDR_IN ;
typedef  int /*<<< orphan*/  SOCKADDR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 scalar_t__ bind (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SOCKET
SetUpListener(USHORT Port)
{
    SOCKET sock;
    SOCKADDR_IN server;
    BOOL bSetup = FALSE;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock != INVALID_SOCKET)
    {
        ZeroMemory(&server, sizeof(SOCKADDR_IN));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = Port;

        if (bind(sock, (SOCKADDR*)&server, sizeof(SOCKADDR_IN)) != SOCKET_ERROR)
        {
            if (listen(sock, SOMAXCONN) != SOCKET_ERROR)
            {
                bSetup = TRUE;
            }
            else
            {
                LogEvent(L"listen() failed", WSAGetLastError(), 0, LOG_ERROR);
            }
        }
        else
        {
            LogEvent(L"bind() failed", WSAGetLastError(), 0, LOG_ERROR);
        }
    }
    else
    {
        LogEvent(L"socket() failed", WSAGetLastError(), 0, LOG_ERROR);
    }

    return bSetup ? sock : INVALID_SOCKET;
}