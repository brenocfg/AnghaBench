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
struct TYPE_2__ {unsigned int last_sent_time; int /*<<< orphan*/  in_request; } ;
typedef  TYPE_1__ RpcConnection_http ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 unsigned int GetTickCount () ; 
 scalar_t__ InternetWriteFile (int /*<<< orphan*/ ,void const*,unsigned int,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void const*,unsigned int,char*) ; 

__attribute__((used)) static int rpcrt4_ncacn_http_write(RpcConnection *Connection,
                                 const void *buffer, unsigned int count)
{
  RpcConnection_http *httpc = (RpcConnection_http *) Connection;
  DWORD bytes_written;
  BOOL ret;

  httpc->last_sent_time = ~0U; /* disable idle packet sending */
  ret = InternetWriteFile(httpc->in_request, buffer, count, &bytes_written);
  httpc->last_sent_time = GetTickCount();
  TRACE("%p %p %u -> %s\n", httpc->in_request, buffer, count, ret ? "TRUE" : "FALSE");
  return ret ? bytes_written : -1;
}