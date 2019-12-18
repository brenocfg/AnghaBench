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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int vsock_addr_validate (struct sockaddr_vm*) ; 

int vsock_addr_cast(const struct sockaddr *addr,
		    size_t len, struct sockaddr_vm **out_addr)
{
	if (len < sizeof(**out_addr))
		return -EFAULT;

	*out_addr = (struct sockaddr_vm *)addr;
	return vsock_addr_validate(*out_addr);
}