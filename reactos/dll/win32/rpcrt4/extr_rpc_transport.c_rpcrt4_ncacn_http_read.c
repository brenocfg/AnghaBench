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
struct TYPE_2__ {int /*<<< orphan*/  cancel_event; int /*<<< orphan*/  async_data; int /*<<< orphan*/  out_request; } ;
typedef  TYPE_1__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RpcConnection ;

/* Variables and functions */
 int rpcrt4_http_async_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static int rpcrt4_ncacn_http_read(RpcConnection *Connection,
                                void *buffer, unsigned int count)
{
  RpcConnection_http *httpc = (RpcConnection_http *) Connection;
  return rpcrt4_http_async_read(httpc->out_request, httpc->async_data, httpc->cancel_event, buffer, count);
}