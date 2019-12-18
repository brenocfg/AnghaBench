#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  AdapterIndex; } ;
struct TYPE_10__ {int /*<<< orphan*/  dwSpeed; int /*<<< orphan*/  dwMtu; int /*<<< orphan*/  dwType; } ;
struct TYPE_13__ {TYPE_1__ IfMib; } ;
struct TYPE_11__ {int /*<<< orphan*/  Speed; int /*<<< orphan*/  Mtu; int /*<<< orphan*/  MediaType; int /*<<< orphan*/  AdapterIndex; } ;
struct TYPE_12__ {int Reply; TYPE_2__ QueryHWInfo; } ;
typedef  int /*<<< orphan*/  (* PipeSendFunc ) (TYPE_3__*) ;
typedef  TYPE_4__* PDHCP_ADAPTER ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_5__ COMM_DHCP_REQ ;
typedef  TYPE_3__ COMM_DHCP_REPLY ;

/* Variables and functions */
 TYPE_4__* AdapterFindIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ApiLock () ; 
 int /*<<< orphan*/  ApiUnlock () ; 

DWORD DSQueryHWInfo( PipeSendFunc Send, COMM_DHCP_REQ *Req ) {
    COMM_DHCP_REPLY Reply;
    PDHCP_ADAPTER Adapter;

    ApiLock();

    Adapter = AdapterFindIndex( Req->AdapterIndex );

    Reply.Reply = Adapter ? 1 : 0;

    if (Adapter) {
        Reply.QueryHWInfo.AdapterIndex = Req->AdapterIndex;
        Reply.QueryHWInfo.MediaType = Adapter->IfMib.dwType;
        Reply.QueryHWInfo.Mtu = Adapter->IfMib.dwMtu;
        Reply.QueryHWInfo.Speed = Adapter->IfMib.dwSpeed;
    }

    ApiUnlock();

    return Send( &Reply );
}