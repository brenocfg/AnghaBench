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
typedef  void* u32 ;
struct sockaddr_vm {void* svm_port; void* svm_cid; int /*<<< orphan*/  svm_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_VSOCK ; 
 int /*<<< orphan*/  memset (struct sockaddr_vm*,int /*<<< orphan*/ ,int) ; 

void vsock_addr_init(struct sockaddr_vm *addr, u32 cid, u32 port)
{
	memset(addr, 0, sizeof(*addr));
	addr->svm_family = AF_VSOCK;
	addr->svm_cid = cid;
	addr->svm_port = port;
}