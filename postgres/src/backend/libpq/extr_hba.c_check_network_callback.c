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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct TYPE_2__ {scalar_t__ method; int /*<<< orphan*/  raddr; void* result; } ;
typedef  TYPE_1__ check_network_data ;

/* Variables and functions */
 void* check_ip (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr*) ; 
 scalar_t__ ipCmpSameHost ; 
 int /*<<< orphan*/  pg_sockaddr_cidr_mask (struct sockaddr_storage*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_network_callback(struct sockaddr *addr, struct sockaddr *netmask,
					   void *cb_data)
{
	check_network_data *cn = (check_network_data *) cb_data;
	struct sockaddr_storage mask;

	/* Already found a match? */
	if (cn->result)
		return;

	if (cn->method == ipCmpSameHost)
	{
		/* Make an all-ones netmask of appropriate length for family */
		pg_sockaddr_cidr_mask(&mask, NULL, addr->sa_family);
		cn->result = check_ip(cn->raddr, addr, (struct sockaddr *) &mask);
	}
	else
	{
		/* Use the netmask of the interface itself */
		cn->result = check_ip(cn->raddr, addr, netmask);
	}
}