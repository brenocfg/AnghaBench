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
struct rpc_iostats {scalar_t__ om_error_status; void* om_execute; void* om_rtt; void* om_queue; scalar_t__ om_bytes_recv; scalar_t__ om_bytes_sent; scalar_t__ om_timeouts; scalar_t__ om_ntrans; scalar_t__ om_ops; } ;

/* Variables and functions */
 void* ktime_add (void*,void*) ; 

__attribute__((used)) static void _add_rpc_iostats(struct rpc_iostats *a, struct rpc_iostats *b)
{
	a->om_ops += b->om_ops;
	a->om_ntrans += b->om_ntrans;
	a->om_timeouts += b->om_timeouts;
	a->om_bytes_sent += b->om_bytes_sent;
	a->om_bytes_recv += b->om_bytes_recv;
	a->om_queue = ktime_add(a->om_queue, b->om_queue);
	a->om_rtt = ktime_add(a->om_rtt, b->om_rtt);
	a->om_execute = ktime_add(a->om_execute, b->om_execute);
	a->om_error_status += b->om_error_status;
}