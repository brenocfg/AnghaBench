#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* authorize ) (TYPE_2__*,int /*<<< orphan*/ ,unsigned char*,unsigned int,unsigned char*,unsigned int*) ;} ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,unsigned char*,unsigned int,unsigned char*,unsigned int*) ; 

__attribute__((used)) static inline RPC_STATUS rpcrt4_conn_authorize(
    RpcConnection *conn, BOOL first_time, unsigned char *in_buffer,
    unsigned int in_len, unsigned char *out_buffer, unsigned int *out_len)
{
    return conn->ops->authorize(conn, first_time, in_buffer, in_len, out_buffer, out_len);
}