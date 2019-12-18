#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_S_OK ; 

__attribute__((used)) static RPC_STATUS rpcrt4_ncalrpc_authorize(RpcConnection *conn, BOOL first_time,
                                           unsigned char *in_buffer,
                                           unsigned int in_size,
                                           unsigned char *out_buffer,
                                           unsigned int *out_size)
{
    /* since this protocol is local to the machine there is no need to
     * authenticate the caller */
    *out_size = 0;
    return RPC_S_OK;
}