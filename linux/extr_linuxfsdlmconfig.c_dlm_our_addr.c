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
struct TYPE_2__ {int addr_count; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 TYPE_1__* local_comm ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

int dlm_our_addr(struct sockaddr_storage *addr, int num)
{
	if (!local_comm)
		return -1;
	if (num + 1 > local_comm->addr_count)
		return -1;
	memcpy(addr, local_comm->addr[num], sizeof(*addr));
	return 0;
}