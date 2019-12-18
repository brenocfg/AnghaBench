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
struct sockaddr_vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMADDR_CID_ANY ; 
 int /*<<< orphan*/  VMADDR_PORT_ANY ; 
 int /*<<< orphan*/  vsock_addr_init (struct sockaddr_vm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vsock_addr_unbind(struct sockaddr_vm *addr)
{
	vsock_addr_init(addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
}