#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int LiVnMode; TYPE_1__ TransmitTimestamp; } ;
struct TYPE_7__ {int /*<<< orphan*/  ntpAddr; TYPE_3__ SendPacket; int /*<<< orphan*/  Sock; } ;
typedef  TYPE_1__ TIMEPACKET ;
typedef  int /*<<< orphan*/  SOCKADDR_IN ;
typedef  int /*<<< orphan*/  SOCKADDR ;
typedef  TYPE_2__* PINFO ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetTransmitTime (TYPE_1__*) ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL
SendData(PINFO pInfo)
{
    TIMEPACKET tp = { 0, 0 };
    INT Ret;

    ZeroMemory(&pInfo->SendPacket, sizeof(pInfo->SendPacket));
    pInfo->SendPacket.LiVnMode = 0x1b;        /* 0x1b = 011 011 - version 3 , mode 3 (client) */
    if (!GetTransmitTime(&tp))
        return FALSE;
    pInfo->SendPacket.TransmitTimestamp = tp;

    Ret = sendto(pInfo->Sock,
                 (char *)&pInfo->SendPacket,
                 sizeof(pInfo->SendPacket),
                 0,
                 (SOCKADDR *)&pInfo->ntpAddr,
                 sizeof(SOCKADDR_IN));

    if (Ret == SOCKET_ERROR)
        return FALSE;

    return TRUE;
}