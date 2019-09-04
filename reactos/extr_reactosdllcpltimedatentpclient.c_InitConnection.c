#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_8__ {struct in_addr sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_7__ {scalar_t__ h_addr; } ;
struct TYPE_6__ {scalar_t__ Sock; TYPE_4__ ntpAddr; } ;
typedef  int /*<<< orphan*/  SOCKADDR_IN ;
typedef  TYPE_1__* PINFO ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ INT ;
typedef  TYPE_2__ HOSTENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  NTPPORT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_4__*,int) ; 
 TYPE_2__* gethostbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
InitConnection(PINFO pInfo,
               LPSTR lpAddress)
{
    WSADATA wsaData;
    HOSTENT *he;
    INT Ret;

    Ret = WSAStartup(MAKEWORD(2, 2),
                     &wsaData);
    if (Ret != 0)
        return FALSE;

    pInfo->Sock = socket(AF_INET,
                         SOCK_DGRAM,
                         0);
    if (pInfo->Sock == INVALID_SOCKET)
        return FALSE;

    /* Setup server info */
    he = gethostbyname(lpAddress);
    if (he != NULL)
    {
        /* Setup server socket info */
        ZeroMemory(&pInfo->ntpAddr, sizeof(SOCKADDR_IN));
        pInfo->ntpAddr.sin_family = AF_INET; // he->h_addrtype;
        pInfo->ntpAddr.sin_port = htons(NTPPORT);
        pInfo->ntpAddr.sin_addr = *((struct in_addr *)he->h_addr);
    }
    else
        return FALSE;

    return TRUE;
}