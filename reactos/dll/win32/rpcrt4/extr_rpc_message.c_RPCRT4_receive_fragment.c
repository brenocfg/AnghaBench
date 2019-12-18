#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* receive_fragment ) (TYPE_2__*,int /*<<< orphan*/ **,void**) ;} ;
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRT4_default_receive_fragment (TYPE_2__*,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ **,void**) ; 

__attribute__((used)) static RPC_STATUS RPCRT4_receive_fragment(RpcConnection *Connection, RpcPktHdr **Header, void **Payload)
{
    if (Connection->ops->receive_fragment)
        return Connection->ops->receive_fragment(Connection, Header, Payload);
    else
        return RPCRT4_default_receive_fragment(Connection, Header, Payload);
}