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
struct vsock_sock {int dummy; } ;
struct sockaddr_vm {int dummy; } ;
struct TYPE_2__ {int (* dgram_bind ) (struct vsock_sock*,struct sockaddr_vm*) ;} ;

/* Variables and functions */
 int stub1 (struct vsock_sock*,struct sockaddr_vm*) ; 
 TYPE_1__* transport ; 

__attribute__((used)) static int __vsock_bind_dgram(struct vsock_sock *vsk,
			      struct sockaddr_vm *addr)
{
	return transport->dgram_bind(vsk, addr);
}