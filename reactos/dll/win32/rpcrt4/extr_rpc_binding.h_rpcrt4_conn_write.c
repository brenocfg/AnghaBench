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
struct TYPE_5__ {int (* write ) (TYPE_2__*,void const*,unsigned int) ;} ;
typedef  TYPE_2__ RpcConnection ;

/* Variables and functions */
 int stub1 (TYPE_2__*,void const*,unsigned int) ; 

__attribute__((used)) static inline int rpcrt4_conn_write(RpcConnection *Connection,
                     const void *buffer, unsigned int len)
{
  return Connection->ops->write(Connection, buffer, len);
}