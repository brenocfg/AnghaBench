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
struct TYPE_2__ {int /*<<< orphan*/ * pub; scalar_t__* prv; } ;
struct sockaddr_atmsvc {scalar_t__ sas_family; TYPE_1__ sas_addr; } ;

/* Variables and functions */
 scalar_t__ AF_ATMSVC ; 
 int ATM_E164_LEN ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 

__attribute__((used)) static int check_addr(const struct sockaddr_atmsvc *addr)
{
	int i;

	if (addr->sas_family != AF_ATMSVC)
		return -EAFNOSUPPORT;
	if (!*addr->sas_addr.pub)
		return *addr->sas_addr.prv ? 0 : -EINVAL;
	for (i = 1; i < ATM_E164_LEN + 1; i++)	/* make sure it's \0-terminated */
		if (!addr->sas_addr.pub[i])
			return 0;
	return -EINVAL;
}