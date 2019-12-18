#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct protocol {int dummy; } ;
struct TYPE_18__ {TYPE_2__* client; int /*<<< orphan*/  rfdesc; int /*<<< orphan*/  name; } ;
struct TYPE_17__ {int /*<<< orphan*/  AdapterIndex; } ;
struct TYPE_13__ {scalar_t__ state; } ;
struct TYPE_16__ {TYPE_7__ DhclientInfo; TYPE_1__ DhclientState; } ;
struct TYPE_15__ {int Reply; } ;
struct TYPE_14__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  (* PipeSendFunc ) (TYPE_3__*) ;
typedef  TYPE_4__* PDHCP_ADAPTER ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_5__ COMM_DHCP_REQ ;
typedef  TYPE_3__ COMM_DHCP_REPLY ;

/* Variables and functions */
 TYPE_4__* AdapterFindIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AdapterStateChangedEvent ; 
 int /*<<< orphan*/  ApiLock () ; 
 int /*<<< orphan*/  ApiUnlock () ; 
 int /*<<< orphan*/  S_INIT ; 
 scalar_t__ S_STATIC ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_protocol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 struct protocol* find_protocol_by_adapter (TYPE_7__*) ; 
 int /*<<< orphan*/  got_one ; 
 int /*<<< orphan*/  remove_protocol (struct protocol*) ; 
 int /*<<< orphan*/  state_reboot (TYPE_7__*) ; 

DWORD DSRenewIpAddressLease( PipeSendFunc Send, COMM_DHCP_REQ *Req ) {
    COMM_DHCP_REPLY Reply;
    PDHCP_ADAPTER Adapter;
    struct protocol* proto;

    ApiLock();

    Adapter = AdapterFindIndex( Req->AdapterIndex );

    if( !Adapter || Adapter->DhclientState.state == S_STATIC ) {
        Reply.Reply = 0;
        ApiUnlock();
        return Send( &Reply );
    }

    Reply.Reply = 1;

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

    ApiUnlock();

    return Send( &Reply );
}