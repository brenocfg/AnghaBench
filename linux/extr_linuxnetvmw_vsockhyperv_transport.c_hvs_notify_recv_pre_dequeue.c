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
struct vsock_transport_recv_notify_data {int dummy; } ;
struct vsock_sock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static
int hvs_notify_recv_pre_dequeue(struct vsock_sock *vsk, size_t target,
				struct vsock_transport_recv_notify_data *d)
{
	return 0;
}