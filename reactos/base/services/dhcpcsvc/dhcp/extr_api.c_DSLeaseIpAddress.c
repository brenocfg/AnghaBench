#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct protocol {int dummy; } ;
struct TYPE_16__ {TYPE_1__* client; int /*<<< orphan*/  rfdesc; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  AdapterIndex; } ;
struct TYPE_14__ {TYPE_6__ DhclientInfo; } ;
struct TYPE_13__ {int Reply; } ;
struct TYPE_12__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  (* PipeSendFunc ) (TYPE_2__*) ;
typedef  TYPE_3__* PDHCP_ADAPTER ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_4__ COMM_DHCP_REQ ;
typedef  TYPE_2__ COMM_DHCP_REPLY ;

/* Variables and functions */
 TYPE_3__* AdapterFindIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AdapterStateChangedEvent ; 
 int /*<<< orphan*/  ApiLock () ; 
 int /*<<< orphan*/  ApiUnlock () ; 
 int /*<<< orphan*/  S_INIT ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_protocol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 struct protocol* find_protocol_by_adapter (TYPE_6__*) ; 
 int /*<<< orphan*/  got_one ; 
 int /*<<< orphan*/  remove_protocol (struct protocol*) ; 
 int /*<<< orphan*/  state_reboot (TYPE_6__*) ; 

DWORD DSLeaseIpAddress( PipeSendFunc Send, COMM_DHCP_REQ *Req ) {
    COMM_DHCP_REPLY Reply;
    PDHCP_ADAPTER Adapter;
    struct protocol* proto;

    ApiLock();

    Adapter = AdapterFindIndex( Req->AdapterIndex );

    Reply.Reply = Adapter ? 1 : 0;

    if( Adapter ) {
        proto = find_protocol_by_adapter( &Adapter->DhclientInfo );
        if (proto)
            remove_protocol(proto);

        add_protocol( Adapter->DhclientInfo.name,
                      Adapter->DhclientInfo.rfdesc, got_one,
                      &Adapter->DhclientInfo );

        Adapter->DhclientInfo.client->state = S_INIT;
        state_reboot(&Adapter->DhclientInfo);

        if (AdapterStateChangedEvent != NULL)
            SetEvent(AdapterStateChangedEvent);
    }

    ApiUnlock();

    return Send( &Reply );
}