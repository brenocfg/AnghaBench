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
struct sockaddr_vm {scalar_t__ svm_family; scalar_t__* svm_zero; } ;

/* Variables and functions */
 scalar_t__ AF_VSOCK ; 
 int EAFNOSUPPORT ; 
 int EFAULT ; 
 int EINVAL ; 

int vsock_addr_validate(const struct sockaddr_vm *addr)
{
	if (!addr)
		return -EFAULT;

	if (addr->svm_family != AF_VSOCK)
		return -EAFNOSUPPORT;

	if (addr->svm_zero[0] != 0)
		return -EINVAL;

	return 0;
}