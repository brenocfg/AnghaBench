#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct socket {int dummy; } ;
struct rxrpc_call {TYPE_2__* conn; } ;
struct TYPE_3__ {int /*<<< orphan*/  epoch; } ;
struct TYPE_4__ {TYPE_1__ proto; } ;

/* Variables and functions */

u32 rxrpc_kernel_get_epoch(struct socket *sock, struct rxrpc_call *call)
{
	return call->conn->proto.epoch;
}