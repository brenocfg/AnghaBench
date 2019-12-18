#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cancel_event; } ;
typedef  TYPE_1__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpcrt4_ncacn_http_cancel_call(RpcConnection *Connection)
{
  RpcConnection_http *httpc = (RpcConnection_http *) Connection;

  SetEvent(httpc->cancel_event);
}