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
struct sockaddr_vm {scalar_t__ svm_cid; scalar_t__ svm_port; } ;

/* Variables and functions */

bool vsock_addr_equals_addr(const struct sockaddr_vm *addr,
			    const struct sockaddr_vm *other)
{
	return addr->svm_cid == other->svm_cid &&
		addr->svm_port == other->svm_port;
}